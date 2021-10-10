#include "../electron-gui/node_modules/node-addon-api/napi.h"
#include "backend.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return backend::Init(env, exports);
}

NODE_API_MODULE(backend, InitAll)
