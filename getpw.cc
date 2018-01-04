/* getpwuid
 *
 * node binding for getpwuid function
 */

#include <sys/types.h> // for struct passwd
#include <pwd.h>       // for getpwuid
#include <errno.h>     // for errno

#include <node.h>

using namespace v8;

// some handy macros that make this V8 interface a lot more concise
#define Q(sym) String::NewFromUtf8(isolate, #sym)
#define S(str) String::NewFromUtf8(isolate, str)
#define I(num) Integer::New(isolate, num)
#define O()    Object::New(isolate)

static inline Local<Value> wrap(Isolate *isolate, int val) { return I(val); }
static inline Local<Value> wrap(Isolate *isolate, const char *val) { return S(val); }

#define SET(obj, sym, val) ((obj)->Set((sym), wrap(isolate, val)))
#define SETQ(obj, sym, val) SET(obj, Q(sym), (val))

// copy field from source struct/class pointer to field of same name in target v8 Object
#define CLONE(tgt, field, src) SETQ(tgt, field, src->field)

void wrapped_getpwuid(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::Error(S("getpwuid requires 1 argument")));
    return;
  }

  int uid;

  if (args[0]->IsNumber()) {
    uid = args[0]->Int32Value();
  } else {
    isolate->ThrowException(Exception::Error(S("getpwuid argument must be a number")));
    return;
  }

  struct passwd *pwd;

  // note this call is blocking
  if ((pwd = getpwuid(uid)) == NULL && errno != 0) {
    isolate->ThrowException(node::ErrnoException(isolate, errno, "getpwuid"));
    return;
  }

  if (pwd == NULL) {
    args.GetReturnValue().Set(Null(isolate));
    return;
  }

  Local<Object> o = O();
  CLONE(o, pw_name,  pwd);
  CLONE(o, pw_uid,   pwd);
  CLONE(o, pw_gid,   pwd);
  CLONE(o, pw_dir,   pwd);
  CLONE(o, pw_shell, pwd);

  args.GetReturnValue().Set(o);
}

void getpw_init(Local<Object> exports)
{
  NODE_SET_METHOD(exports, "getpwuid", wrapped_getpwuid);
}

NODE_MODULE(getpw, getpw_init)
