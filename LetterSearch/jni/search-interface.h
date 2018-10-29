/*
 * search_interface.h
 *
 *  Created on: 2015Äê12ÔÂ5ÈÕ
 *      Author: Andme
 */

#ifndef SEARCH_INTERFACE_H_
#define SEARCH_INTERFACE_H_

extern jboolean searchPinyinFromJNI(JNIEnv* env, jobject thiz,
		jobjectArray source, jstring input, jintArray colors);

extern jboolean searchMorePinyinFromJNI(JNIEnv* env, jobject thiz,
		jobjectArray source, jstring input, jintArray colors);

#endif /* SEARCH_INTERFACE_H_*/
