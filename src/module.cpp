#include <napi.h>

#include "JsObject.h"


Napi::Object Init(Napi::Env env, Napi::Object exports)
{
	return JsObject::InitJsApi(env, exports);
}

NODE_API_MODULE(module, Init)
