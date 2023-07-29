var addon = require('./build/Release/hello.node')

const mock_object = {
    a: 4,
    test_func: () => 290
};

console.log(addon.js_require(module));