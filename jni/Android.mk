LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := NDKBegin
LOCAL_SRC_FILES := NDKBegin.cpp
LOCAL_LDLIBS := -llog 
include $(BUILD_SHARED_LIBRARY)