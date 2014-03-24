#include <ctype.h>
#include <node.h>
#include <stdlib.h>
#include <string.h>

#include "vercmp.h"

using namespace v8;

/* the following is stolen from dpkg */
/* assume ascii; warning: evaluates x multiple times! */
#define order(x) ((x) == '~' ? -1 \
    : isdigit((x)) ? 0 \
    : !(x) ? 0 \
    : isalpha((x)) ? (x) \
    : (x) + 256)

static int verrevcmp(const char *val, const char *ref) {
  if (!val) val= "";
  if (!ref) ref= "";

  while (*val || *ref) {
    int first_diff= 0;

    while ( (*val && !isdigit(*val)) || (*ref && !isdigit(*ref)) ) {
      int vc= order(*val), rc= order(*ref);
      if (vc != rc) return vc - rc;
      val++; ref++;
    }

    while ( *val == '0' ) val++;
    while ( *ref == '0' ) ref++;
    while (isdigit(*val) && isdigit(*ref)) {
      if (!first_diff) first_diff= *val - *ref;
      val++; ref++;
    }
    if (isdigit(*val)) return 1;
    if (isdigit(*ref)) return -1;
    if (first_diff) return first_diff;
  }
  return 0;
}

int vercmp(const string &a, const string &b) {
  string aepoch, bepoch;
  string aversion, bversion;
  string arevision, brevision;
  int r;

  /* compare the epochs */
  string::size_type i = a.find(':', 0);
  if (i == string::npos) {
    aepoch = "0";
    aversion = a;
  }
  else {
    aepoch = a.substr(0, i);
    aversion = a.substr(i + 1, a.length());
  }
  i = b.find(':', 0);
  if (i == string::npos) {
    bepoch = "0";
    bversion = b;
  }
  else {
    bepoch = b.substr(0, i);
    bversion = b.substr(i + 1, b.length());
  }
  if ((r = verrevcmp(aepoch.c_str(), bepoch.c_str())) != 0)
    return r;

  /* compare the versions */
  i = aversion.rfind('-', a.length());
  if (i == string::npos) {
    arevision = "0";
  }
  else {
    arevision = aversion.substr(i + 1, aversion.length());
    aversion = aversion.substr(0, i);
  }
  i = bversion.rfind('-', b.length());
  if (i == string::npos) {
    brevision = "0";
  }
  else {
    brevision = bversion.substr(i + 1, bversion.length());
    bversion = bversion.substr(0, i);
  }
  if ((r = verrevcmp(aversion.c_str(), bversion.c_str())) != 0)
    return r;
  return verrevcmp(arevision.c_str(), brevision.c_str());
}

char *get(v8::Local<v8::Value> value, const char *fallback = "") {
    if (value->IsString()) {
        v8::String::AsciiValue string(value);
        char *str = (char *) malloc(string.length() + 1);
        strcpy(str, *string);
        return str;
    }
    char *str = (char *) malloc(strlen(fallback) + 1);
    strcpy(str, fallback);
    return str;
}

// Simple synchronous access to the `Estimate()` function
Handle<Value> Compare(const Arguments& args) {
  HandleScope scope;

  // expect a number as the first argument
  // int points = args[0]->Uint32Value();
  int est = vercmp(get(args[0], "0.0.0"), get(args[1], "0.0.0"));

  return scope.Close(Number::New(est));
}

void Init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("vercmp"),
      FunctionTemplate::New(Compare)->GetFunction());
}

NODE_MODULE(vercmp, Init)