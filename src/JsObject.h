#pragma once

#include <NapiHelpers.h>


class JsObject : public Napi::ObjectWrap<JsObject>
{
	static Napi::FunctionReference _jsConstructor;

public:
	static Napi::Object InitJsApi(Napi::Env env, Napi::Object exports);

	JsObject(const Napi::CallbackInfo&);
	~JsObject();

private:
	bool foo(int n);
};
