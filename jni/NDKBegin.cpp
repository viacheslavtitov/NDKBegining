#include <jni.h>
#include <string.h>
#include <eleks_com_ndk_begin_app_MainActivity.h>
#include <android/log.h>
#include <stdio.h>
/*
 * Class:     eleks_com_ndk_begin_app_MainActivity
 * Method:    getStringFromFile
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */JNIEXPORT jstring JNICALL Java_eleks_com_ndk_begin_app_MainActivity_getStringFromFile(
		JNIEnv *env, jobject obj, jstring path) {
	jclass errorClass;
	char buff[1024];
	FILE *f = fopen(env->GetStringUTFChars(path, NULL), "r");
	if (f != NULL) {
		if (fgets(buff, 1024, f) != NULL) {
			__android_log_print(ANDROID_LOG_VERBOSE, "MyTag", "String read: %s",
					buff);
		} else {
			__android_log_print(ANDROID_LOG_ERROR, "MyTag", "File read error");
			errorClass = env->FindClass("java/io/FileNotFoundException");
			env->ThrowNew(errorClass, "File read exception");
		}
		if (fclose(f) == EOF) {
			__android_log_print(ANDROID_LOG_ERROR, "MyTag", "file close error");
			errorClass = env->FindClass("java/io/IOException");
			env->ThrowNew(errorClass, "File close exception");
		}
		return env->NewStringUTF(buff);
	} else {
		errorClass = env->FindClass("java/io/FileNotFoundException");
		env->ThrowNew(errorClass, "File not found");
		return NULL;
	}
}

/*
 * Class:     eleks_com_ndk_begin_app_MainActivity
 * Method:    writeByteArrayToFile
 * Signature: ([B)V
 */JNIEXPORT void JNICALL Java_eleks_com_ndk_begin_app_MainActivity_writeByteArrayToFile(
		JNIEnv *env, jobject obj, jstring path, jbyteArray data) {
	jclass errorClass;
	char* a = (char*) env->GetByteArrayElements(data, NULL);
	FILE *f = fopen(env->GetStringUTFChars(path, NULL), "w");
	if (f != NULL) {
		__android_log_print(ANDROID_LOG_VERBOSE, "MyTag", "String write: %s",
				a);
		if (fputs(a, f) == EOF) {
			__android_log_print(ANDROID_LOG_ERROR, "MyTag", "file write error");
			errorClass = env->FindClass("java/io/IOException");
			env->ThrowNew(errorClass, "File write exception");
		}
		if (fclose(f) == EOF) {
			__android_log_print(ANDROID_LOG_ERROR, "MyTag", "file close error");
			errorClass = env->FindClass("java/io/IOException");
			env->ThrowNew(errorClass, "File close exception");
		}
	} else {
		__android_log_print(ANDROID_LOG_ERROR, "MyTag", "file not found");
		errorClass = env->FindClass("java/io/FileNotFoundException");
		env->ThrowNew(errorClass, "File not found");
	}
}
