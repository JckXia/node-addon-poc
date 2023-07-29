#include <napi.h>

Napi::Function GetJsRequireFunction(const Napi::CallbackInfo &info) 
{
  Napi::Env env = info.Env();
  Napi::Object module_object = info[0].As<Napi::Object>();
  Napi::Function require =  module_object.Get("require").As<Napi::Function>();
  return require;
}

// Small POC to demonstrate using `path.join` from C++
Napi::Value CallJoinFromCppLand(const Napi::CallbackInfo& info)
{

  Napi::Env env = info.Env();
  Napi::String module_name = Napi::String::New(env, "path");
  Napi::Function require = GetJsRequireFunction(info);

  // Get the 'path' corelib from node, as an Object
  Napi::Object jsPathLib = require.Call({module_name}).As<Napi::Object>();
  
  // Get the `join` function from the path object. This has to be a Napi::Function type
  Napi::Function pathJoin = jsPathLib.Get("join").As<Napi::Function>();

  // Prepare args
  Napi::String protcol = Napi::String::New(env, "https");
  Napi::String domain = Napi::String::New(env, "pagerduty");
  Napi::String uri = Napi::String::New(env, "api");
  
  // invoke the `join` function and provide it with some arguments
  //    -> Functions can be invoked with either initialization lists or else.
  Napi::Value results = pathJoin.Call({protcol, domain, uri});
  return results;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("cc_require", Napi::Function::New(env,CallJoinFromCppLand));
  return exports;
}

NODE_API_MODULE(hello, Init)