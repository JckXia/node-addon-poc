var addon = require('./build/Release/hello.node')

// The article linked talked a little bit about commonjs module implementations.
// IIUC The `require` is a function attached to the `module` object. To use it we need to 
// hand this off to node-addon-api. 

// This will print out https/pagerduty/api, which acts
// as if we invoked path.join('https','pagerduty','api') from js
console.log(addon.js_require(module));