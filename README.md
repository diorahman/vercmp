# vercmp

In short, it is one of tools to answer following question: http://stackoverflow.com/questions/4957514/how-to-compare-debian-package-versions but in node.

[![Build Status](https://travis-ci.org/diorahman/vercmp.svg?branch=master)](https://travis-ci.org/diorahman/vercmp)

## install

```
npm -i vercmp --save
```

## usage example

```js
vercmp('0.0.1', '0.0.1'); // == 0
vercmp('0.0.2', '0.0.1'); // == 1
vercmp('0.0.1', '0.0.2'); // == -1
```

## license 

MIT
