# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := frida-gum
LOCAL_SRC_FILES := frida-gum/libs/$(TARGET_ARCH_ABI)/libfrida-gum.a
include $(PREBUILT_STATIC_LIBRARY) 

include $(CLEAR_VARS)
# LOCAL_ARM_MODE := arm
LOCAL_MODULE    := substrate
LOCAL_SRC_FILES := substrate.c

LOCAL_STATIC_LIBRARIES += frida-gum
LOCAL_LDLIBS := -llog


LOCAL_CFLAGS := -fvisibility=hidden


include $(BUILD_SHARED_LIBRARY)
# include $(BUILD_EXECUTABLE)





# include $(CLEAR_VARS)

# LOCAL_MODULE    := hello1
# LOCAL_SRC_FILES := hello.c
# include $(BUILD_SHARED_LIBRARY)
