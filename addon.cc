#include <napi.h>


Napi::Function GetJsRequireFunction(const Napi::CallbackInfo &info) 
{
  Napi::Env env = info.Env();

  Napi::Object module_object = info[0].As<Napi::Object>();
  Napi::String module_name = Napi::String::New(env, "path");
  Napi::Function require =  module_object.Get("require").As<Napi::Function>();
  return require;
}
Napi::Value CallRequire(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Object module_object = info[0].As<Napi::Object>();
  Napi::String module_name = Napi::String::New(env, "path");
  Napi::Function require =  module_object.Get("require").As<Napi::Function>();
  
  // The
  Napi::Object jsPathLib = require.Call({module_name}).As<Napi::Object>();
  
  Napi::Function pathJoin = jsPathLib.Get("join").As<Napi::Function>();

  Napi::String pathArgs = Napi::String::New(env, "arggh");
  Napi::String domain = Napi::String::New(env, "pagerduty");
  Napi::Value results = pathJoin.Call({pathArgs, domain});
  return results;
}
Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set("js_require", Napi::Function::New(env,CallRequire));
  return exports;
}

NODE_API_MODULE(hello, Init)