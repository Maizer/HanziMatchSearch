/*
 * search_interface.c
 *
 *  Created on: 2015年12月7日
 *      Author: Andme
 */
#include <string.h>
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <android/log.h>
#include <search-interface.h>
#include <sys/types.h>
#include <sys/file.h>

#define  LOG_TAG    "libplasma"
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

jboolean searchPinyinFromJNI(JNIEnv* env, jobject thiz, jobjectArray source,
		jstring input, jintArray colors) {
	const jchar* inputchars = (*env)->GetStringChars(env, input, JNI_FALSE);
	jsize inputjarray_length = (*env)->GetStringLength(env, input);

	int sourceLetter = 0, letterIndex = 0, inputIndex = 0, start = -1, end = 0;
	jsize source_length = (*env)->GetArrayLength(env, source);

	jstring source_element = (jstring) (*env)->GetObjectArrayElement(env,
			source, sourceLetter);
	const jchar* sourcechars = (*env)->GetStringChars(env, source_element,
	JNI_FALSE);

	jsize sourcechars_length = (*env)->GetStringLength(env, source_element);

	while (inputIndex > -1 && inputIndex < inputjarray_length
			&& sourceLetter < source_length) {
		// 用来检测空字符
		if (sourcechars_length == 1 && sourcechars[0] == ' ') {
			sourceLetter++;
			if (sourceLetter >= source_length) {
				break;
			}
			// 由于底层的结构,为了将内存降到最低
			(*env)->ReleaseStringChars(env, source_element, sourcechars);
			(*env)->DeleteLocalRef(env, source_element);
			source_element = (jstring) (*env)->GetObjectArrayElement(env,
					source, sourceLetter);
			sourcechars = (*env)->GetStringChars(env, source_element,
			JNI_FALSE);
			sourcechars_length = (*env)->GetStringLength(env, source_element);
		} else if (inputchars[inputIndex] == sourcechars[letterIndex]) {
			letterIndex++;
			inputIndex++;
			if (start == -1) {
				start = sourceLetter;
			}
			end = sourceLetter;
			if (inputIndex == inputjarray_length) {
				break;
			} else if (letterIndex == sourcechars_length) {
				letterIndex = 0;
				sourceLetter++;
				if (sourceLetter >= source_length) {
					break;
				}
				(*env)->ReleaseStringChars(env, source_element, sourcechars);
				(*env)->DeleteLocalRef(env, source_element);

				source_element = (jstring) (*env)->GetObjectArrayElement(env,
						source, sourceLetter);
				sourcechars = (*env)->GetStringChars(env, source_element,
				JNI_FALSE);
				sourcechars_length = (*env)->GetStringLength(env,
						source_element);
			}
		} else if (letterIndex == 0 && inputIndex > 0) {
			inputIndex--;
			if (inputIndex <= 0) {
				start = -1;
			}
		} else {
			letterIndex = 0;
			sourceLetter++;
			if (sourceLetter >= source_length) {
				break;
			}
			(*env)->ReleaseStringChars(env, source_element, sourcechars);
			(*env)->DeleteLocalRef(env, source_element);
			source_element = (jstring) (*env)->GetObjectArrayElement(env,
					source, sourceLetter);
			sourcechars = (*env)->GetStringChars(env, source_element,
			JNI_FALSE);
			sourcechars_length = (*env)->GetStringLength(env, source_element);
		}
	}
	(*env)->ReleaseStringChars(env, source_element, sourcechars);
	(*env)->DeleteLocalRef(env, source);
	(*env)->DeleteLocalRef(env, source_element);
	(*env)->ReleaseStringChars(env, input, inputchars);
	(*env)->DeleteLocalRef(env, input);

	if (inputIndex == inputjarray_length) {
		if (colors != NULL) {
			int csize = (*env)->GetArrayLength(env, colors);
			if (csize >= 2) {
				jint* cs = (*env)->GetIntArrayElements(env, colors,
				JNI_FALSE);
				cs[0] = start;
				cs[1] = end + 1;
				(*env)->ReleaseIntArrayElements(env, colors, cs, JNI_FALSE);
			}
			(*env)->DeleteLocalRef(env, colors);
		}
		return JNI_TRUE;
	}
	return JNI_FALSE;
}
jboolean searchMorePinyinFromJNI(JNIEnv* env, jobject thiz, jobjectArray source,
		jstring input, jintArray colors) {
	const jchar* inputchars = (*env)->GetStringChars(env, input, JNI_FALSE);
	jsize inputjarray_length = (*env)->GetStringLength(env, input);
	short sourceLetter = 0, letterIndex = 0, inputIndex = 0, start = -1,
			end = 0, saveInputEnd = -1, saveInputStart = 0;
	jsize source_length = (*env)->GetArrayLength(env, source);
	jstring source_element = (jstring) (*env)->GetObjectArrayElement(env,
			source, sourceLetter);
	const jchar* sourcechars = (*env)->GetStringChars(env, source_element,
	JNI_FALSE);
	jsize sourcechars_length = (*env)->GetStringLength(env, source_element);
	A: while (inputIndex > -1 && inputIndex < inputjarray_length
			&& sourceLetter < source_length) {
		// 用来检测空字符
		if (sourcechars_length == 1 && sourcechars[0] == ' ') {
			sourceLetter++;
			if (sourceLetter >= source_length) {
				break;
			}
			// 由于底层的结构,为了将内存降到最低
			(*env)->ReleaseStringChars(env, source_element, sourcechars);
			(*env)->DeleteLocalRef(env, source_element);
			source_element = (jstring) (*env)->GetObjectArrayElement(env,
					source, sourceLetter);
			sourcechars = (*env)->GetStringChars(env, source_element,
			JNI_FALSE);
			sourcechars_length = (*env)->GetStringLength(env, source_element);
		} else if (inputchars[inputIndex] == sourcechars[letterIndex]) {
			if (letterIndex == 0) {
				saveInputStart = inputIndex;
			}
			letterIndex++;
			inputIndex++;
			if (start == -1) {
				start = sourceLetter;
			}
			end = sourceLetter;
			if (inputIndex == inputjarray_length) {
				break;
			} else if (letterIndex == sourcechars_length) {
				letterIndex = 0;
				sourceLetter++;
				if (sourceLetter >= source_length) {
					break;
				}
				(*env)->ReleaseStringChars(env, source_element, sourcechars);
				(*env)->DeleteLocalRef(env, source_element);

				source_element = (jstring) (*env)->GetObjectArrayElement(env,
						source, sourceLetter);
				sourcechars = (*env)->GetStringChars(env, source_element,
				JNI_FALSE);
				sourcechars_length = (*env)->GetStringLength(env,
						source_element);
			}
		} else if (letterIndex == 0 && inputIndex > 0) {
			while (letterIndex < sourcechars_length) {
				if (sourcechars[letterIndex] == ' ') {
					if (sourcechars[letterIndex + 1]
							== inputchars[inputIndex]) {
						letterIndex++;
						goto A;
					}
				}
				letterIndex++;
			}
			letterIndex = 0;
			inputIndex--;
			if(inputIndex == saveInputStart){
				inputIndex = 0;
				start = -1;
				continue;
			}
			if (inputIndex <= 0) {
				start = -1;
			}
		} else {
			if (sourcechars_length > 1) {
				while (letterIndex < sourcechars_length) {
					if (sourcechars[letterIndex] == ' '
							&& sourcechars[letterIndex + 1]
									== inputchars[saveInputStart]) {
						if (inputIndex > saveInputEnd) {
							saveInputEnd = inputIndex;
						}
						letterIndex += 2;
						inputIndex = saveInputStart + 1;
						goto A;
					}
					letterIndex++;
				}
				if (saveInputEnd > inputIndex) {
					inputIndex = saveInputEnd;
				}
				saveInputEnd = -1;
			}
			letterIndex = 0;
			sourceLetter++;
			if (sourceLetter >= source_length) {
				break;
			}
			(*env)->ReleaseStringChars(env, source_element, sourcechars);
			(*env)->DeleteLocalRef(env, source_element);
			source_element = (jstring) (*env)->GetObjectArrayElement(env,
					source, sourceLetter);
			sourcechars = (*env)->GetStringChars(env, source_element,
			JNI_FALSE);
			sourcechars_length = (*env)->GetStringLength(env, source_element);
		}
	}
	(*env)->ReleaseStringChars(env, source_element, sourcechars);
	(*env)->DeleteLocalRef(env, source);
	(*env)->DeleteLocalRef(env, source_element);
	(*env)->ReleaseStringChars(env, input, inputchars);
	(*env)->DeleteLocalRef(env, input);

	if (inputIndex == inputjarray_length) {
		if (colors != NULL) {
			int csize = (*env)->GetArrayLength(env, colors);
			if (csize >= 2) {
				jint* cs = (*env)->GetIntArrayElements(env, colors,
				JNI_FALSE);
				cs[0] = start;
				cs[1] = end + 1;
				(*env)->ReleaseIntArrayElements(env, colors, cs, JNI_FALSE);
			}
			(*env)->DeleteLocalRef(env, colors);
		}
		return JNI_TRUE;
	}
	return JNI_FALSE;
}

