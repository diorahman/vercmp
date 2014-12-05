# vercmp

In short, it answers this: http://stackoverflow.com/questions/4957514/how-to-compare-debian-package-versions but in node.

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
