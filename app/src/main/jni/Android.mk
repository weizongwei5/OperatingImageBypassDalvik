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


# Copyright 2014 http://Bither.net
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

LOCAL_PATH := $(call my-dir)


#jpeg-turbo
include $(CLEAR_VARS)
LOCAL_MODULE    := libjpeg
LOCAL_SRC_FILES := libjpeg.so
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE    := bypassdalvik
LOCAL_SRC_FILES := bypassdalvik.c \
										compress.c  	\
										resize.c
LOCAL_SHARED_LIBRARIES := libjpeg
LOCAL_STATIC_LIBRARIES += png
 # 依赖zlib  因为libpng依赖zlib
LOCAL_LDLIBS := -ljnigraphics -llog  -lz
LOCAL_C_INCLUDES := $(LOCAL_PATH) \
                    $(LOCAL_PATH)/libjpeg-turbo \
                    $(LOCAL_PATH)/libjpeg-turbo/android

LOCAL_C_INCLUDES += $(LOCAL_PATH)/libpng


include $(BUILD_SHARED_LIBRARY)

include $(CLEAR_VARS)
include $(LOCAL_PATH)/libpng/Android.mk