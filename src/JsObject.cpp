#include "JsObject.h"

#include <nah/NodeHelpers.h>

v8::Persistent<v8::Function> JsObject::_jsConstructor;
std::set<JsObject*> JsObject::_instances;

void JsObject::initJsApi( const v8::Handle<v8::Object>& exports )
{
    node::AtExit( [] ( void* ) { JsObject::closeAll(); } );

    using namespace v8;

    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope( isolate );

    Local<FunctionTemplate> constructorTemplate = FunctionTemplate::New( isolate, jsCreate );
    constructorTemplate->SetClassName( String::NewFromUtf8( isolate, "JsObject", v8::String::kInternalizedString ) );

    Local<ObjectTemplate> protoTemplate = constructorTemplate->PrototypeTemplate();
    Local<ObjectTemplate> instanceTemplate = constructorTemplate->InstanceTemplate();
    instanceTemplate->SetInternalFieldCount( 1 );

    SET_RO_PROPERTY( instanceTemplate, "bar", &JsObject::bar );

    SET_METHOD( instanceTemplate, "foo", &JsObject::foo );

    Local<Function> constructor = constructorTemplate->GetFunction();
    _jsConstructor.Reset( isolate, constructor );
}

void JsObject::jsCreate( const v8::FunctionCallbackInfo<v8::Value>& args )
{
    using namespace v8;

    Isolate* isolate = Isolate::GetCurrent();
    HandleScope scope( isolate );

    if( args.IsConstructCall() ) {
        Local<Object> thisObject = args.Holder();
        JsObject* jsObject = new JsObject( thisObject );
        args.GetReturnValue().Set( jsObject->handle() );
    } else {
        Local<Value> argv[] = { args[0] };
        Local<Function> constructor =
            Local<Function>::New( isolate, _jsConstructor );
        const size_t argc = sizeof( argv ) / sizeof( argv[0] );
        args.GetReturnValue().Set( constructor->NewInstance( argc, argv ) );
    }
}

void JsObject::closeAll()
{
    for( JsObject* p : _instances ) {
        p->close();
    }
}

JsObject::JsObject( v8::Local<v8::Object>& thisObject )
{
    Wrap( thisObject );

    _instances.insert( this );
}

JsObject::~JsObject()
{
    close();

    _instances.erase( this );
}

void JsObject::close()
{
}

int JsObject::bar()
{
    return 0;
}

bool JsObject::foo( int bar )
{
    return false;
}
