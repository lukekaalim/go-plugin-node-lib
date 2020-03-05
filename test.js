const { createEncodedCert, mark } = require('./index');

console.log(createEncodedCert());
console.log(mark(100, 3, 'network1', 'address1', 'prototype1', 'serverCert1'));