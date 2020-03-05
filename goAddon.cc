// hello.cc using N-API
#include <node_api.h>
#include <stdio.h>
#include <string>
#include "lib/libgo.h"

namespace demo {

  napi_value Method(napi_env env, napi_callback_info args) {
    napi_value greeting;
    napi_status status;

    status = napi_create_string_utf8(env, Cert(), NAPI_AUTO_LENGTH, &greeting);
    if (status != napi_ok) return nullptr;
    return greeting;
  }

  napi_value MarkMethod(napi_env env, napi_callback_info info) {
    napi_value me;
    size_t argsLength = 6; // predicted max numbers of arguments
    napi_value args[6];
    napi_get_cb_info(env, info, &argsLength, args, &me, 0);

    int32_t first_arg;
    int32_t second_arg;
    napi_get_value_int32(env, args[0], &first_arg);
    napi_get_value_int32(env, args[1], &second_arg);
    char* third_arg = new char[256];
    napi_get_value_string_utf8(env, args[2], third_arg, 32, nullptr);
    char* fourth_arg = new char[256];
    napi_get_value_string_utf8(env, args[3], fourth_arg, 32, nullptr);
    char* fifth_arg = new char[256];
    napi_get_value_string_utf8(env, args[4], fifth_arg, 32, nullptr);
    char* sixth_arg = new char[256];
    napi_get_value_string_utf8(env, args[5], sixth_arg, 32, nullptr);

    Mark(first_arg, second_arg, third_arg, fourth_arg, fifth_arg, sixth_arg);
    
    // should do something but here is nothing for the test
    napi_value napi_null;
    napi_get_null(env, &napi_null);
    return napi_null;

    /*
    napi_value result;
    napi_status status;

    size_t args_length = 2;
    napi_value arg_values[2];
    napi_value first_arg_value;
  
    status = napi_get_cb_info(env, info, &args_length, &arg_values, nullptr, nullptr);
    if (status != napi_ok) return nullptr;

    status = napi_get_element(env, arg_values, 2, &first_arg_value);
    if (status != napi_ok) return nullptr;

    napi_valuetype typeof_first_arg_value;

    status = napi_typeof(env, arg_values, &typeof_first_arg_value);
    if (status != napi_ok) return nullptr;

    printf("%d\n", typeof_first_arg_value);

    int32_t first_arg;

    status = napi_get_value_int32(env, first_arg_value, &first_arg);
    if (status != napi_ok) return nullptr;

    printf("hi!");
    printf(std::to_string(first_arg).c_str());

    Mark();
    status = napi_get_null(env, &result);
    if (status != napi_ok) return nullptr;

    return result;
    */
  }

  napi_value init(napi_env env, napi_value exports) {
    napi_status status;
    napi_value fn;
    napi_value markFn;

    status = napi_create_function(env, nullptr, 0, Method, nullptr, &fn);
    if (status != napi_ok) return nullptr;

    status = napi_create_function(env, nullptr, 0, MarkMethod, nullptr, &markFn);
    if (status != napi_ok) return nullptr;

    status = napi_set_named_property(env, exports, "createEncodedCert", fn);
    if (status != napi_ok) return nullptr;

    status = napi_set_named_property(env, exports, "mark", markFn);
    if (status != napi_ok) return nullptr;

    return exports;
  }

  NAPI_MODULE(NODE_GYP_MODULE_NAME, init)

}  // namespace demo
