LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)


LOCAL_MODULE    := search-interface
LOCAL_SRC_FILES := search-interface.c
LOCAL_LDLIBS    := -lm -llog -landroid

include $(BUILD_STATIC_LIBRARY)

# second lib, which will depend on and include the first one
#
include $(CLEAR_VARS)

LOCAL_MODULE    := pinyinsearch
LOCAL_SRC_FILES := pinyinsearch.c
LOCAL_LDLIBS    := -lm -llog -landroid

LOCAL_STATIC_LIBRARIES := search-interface

include $(BUILD_SHARED_LIBRARY)





