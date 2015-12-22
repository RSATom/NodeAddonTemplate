#include <node.h>
#include <v8.h>

#include "JsObject.h"

void Init( v8::Handle<v8::Object> exports, v8::Handle<v8::Object> module )
{
    JsObject::initJsApi( exports );
}

NODE_MODULE( module, Init )
