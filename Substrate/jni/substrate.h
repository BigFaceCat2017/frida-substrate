
#ifndef SUBSTRATE_H_
#define SUBSTRATE_H_

#ifdef __arm__

#include "frida-gum/libs/armeabi-v7a/frida-gum.h"

#elif defined(__aarch64__)

#include "frida-gum/libs/arm64-v8a/frida-gum.h"

#elif  __i386__

#include "frida-gum/libs/x86/frida-gum.h"

#elif  __x86_64__

#include "frida-gum/libs/x86_64/frida-gum.h"

#endif

#include <dlfcn.h>
#include <stdlib.h>
#include <android/log.h>

//Log相关代码
#define LOG_TAG "BigFaceCat"  
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__) // 定义LOGD类型
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__) // 定义LOGI类型 
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__) // 定义LOGW类型 
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__) // 定义LOGE类型 
#define LOGF(...)  __android_log_print(ANDROID_LOG_FATAL,LOG_TAG,__VA_ARGS__) // 定义LOGF类

#ifdef __cplusplus
extern "C" {
#endif


void* MSFindBase(const char * module_name);

void* MSFindSymbol(const char * module_name, const char *name);

void MSHookFunction(void *symbol, void *replace, void **result);

#ifdef __cplusplus
}
#endif

#endif//SUBSTRATE_H_