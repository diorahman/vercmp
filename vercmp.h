#ifndef _VERCMP_H
#define _VERCMP_H

#include <string>
#include <node.h>

using namespace std;

int vercmp(const string &a, const string &b);
v8::Handle<v8::Value> CalculateSync(const v8::Arguments& args);

#endif /* _VERCMP_H */
