#pragma once

#include <set>

#include <v8.h>
#include <node.h>
#include <node_object_wrap.h>

class JsObject : public node::ObjectWrap
{
public:
    static void initJsApi( const v8::Handle<v8::Object>& exports );

private:
    static void jsCreate( const v8::FunctionCallbackInfo<v8::Value>& args );
    static void closeAll();

    JsObject( v8::Local<v8::Object>& thisObject );
    ~JsObject();

    void close();

    int bar();

    bool foo( int n );

private:
    static v8::Persistent<v8::Function> _jsConstructor;
    static std::set<JsObject*> _instances;
};
