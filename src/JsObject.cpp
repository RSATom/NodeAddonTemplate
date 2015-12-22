#include "JsObject.h"


Napi::FunctionReference JsObject::_jsConstructor;

Napi::Object JsObject::InitJsApi(Napi::Env env, Napi::Object exports)
{
	Napi::HandleScope scope(env);

	Napi::Function func =
		DefineClass(env, "JsObject", {
				CLASS_METHOD("foo", &JsObject::foo),
			}
		);

	_jsConstructor = Napi::Persistent(func);
	_jsConstructor.SuppressDestruct();

	exports.Set("JsObject", func);

	return exports;
}


JsObject::JsObject(const Napi::CallbackInfo& info) :
	Napi::ObjectWrap<JsObject>(info)
{
}

JsObject::~JsObject()
{
}

bool JsObject::foo(int bar)
{
	return false;
}
