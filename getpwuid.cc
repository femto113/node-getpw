/* getpwuid
 *
 * node binding for getpwuid function
 */

#include <sys/types.h> // for struct passwd
#include <pwd.h>       // for getpwuid
#include <errno.h>     // for errno

#define BUILDING_NODE_EXTENSION
#include <node.h>

using namespace v8;

// some handy macros that make this V8 interface a lot more concise
#define Q(sym) String::NewSymbol(#sym)
#define S(str) String::New(str)
#define I(num) Integer::New(num)
#define F(fun) FunctionTemplate::New(fun)->GetFunction()
#define O()    Object::New()

static inline Handle<Value> wrap(int val) { return I(val); }
static inline Handle<Value> wrap(const char *val) { return S(val); }

#define SET(obj, sym, val) ((obj)->Set((sym), wrap(val)))
#define SETQ(obj, sym, val) SET(obj, Q(sym), (val))

static Handle<Value> wrapped_getpwuid(const Arguments& args)
{
  HandleScope scope;

  if (args.Length() < 1) {
    return ThrowException(Exception::Error(String::New("getpwuid requires 1 argument")));
  }

  int uid;

  if (args[0]->IsNumber()) {
    uid = args[0]->Int32Value();
  } else {
    return ThrowException(Exception::Error(S("getpwuid argument must be a number")));
  }

  struct passwd *pwd;

  // note this call is blocking
  if ((pwd = getpwuid(uid)) == NULL && errno != 0) {
    return ThrowException(node::ErrnoException(errno, "getpwuid"));
  }

  if (pwd == NULL) {
      return Null();
  }

#define CLONE(tgt, field, src) SETQ(tgt, field, src->field)

  Local<Object> o = O();
  CLONE(o, pw_name,  pwd);
  CLONE(o, pw_uid,   pwd);
  CLONE(o, pw_gid,   pwd);
  CLONE(o, pw_dir,   pwd);
  CLONE(o, pw_shell, pwd);

  return scope.Close(o);
}

void getpwuid_init(Handle<Object> target)
{
  target->Set(Q(getpwuid), F(wrapped_getpwuid));
}

NODE_MODULE(getpwuid, getpwuid_init)
