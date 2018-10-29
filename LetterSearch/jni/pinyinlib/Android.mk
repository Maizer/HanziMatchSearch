LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := hanzitopinyin
LOCAL_SRC_FILES := hanzitopinyin.c
LOCAL_LDLIBS    := -lm -llog -landroid

include $(BUILD_SHARED_LIBRARY)




