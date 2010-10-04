#include <jni.h>
#include <jni_md.h>

#include "RefCache.h"

jint RefCache::setUp(JNIEnv *env) {
	jclass classID;

	int i=0;
	while (classRefCache[i].className != NULL) {
		classID = env->FindClass(classRefCache[i].className);
		if (classID == NULL)
			return JNI_ERR;
		classRefCache[i].classID = (jclass)env->NewWeakGlobalRef(classID);
		i++;
	}
	i=0;
	while (methodRefCache[i].methodName != NULL) {
		classID = classRefCache[methodRefCache[i].classIndex].classID;
		methodRefCache[i].methodID = env->GetMethodID(classID, methodRefCache[i].methodName, methodRefCache[i].methodSignature);
		i++;
	}
	i=0;
	while (fieldRefCache[i].fieldName != NULL) {
		classID = classRefCache[fieldRefCache[i].classIndex].classID;
		fieldRefCache[i].fieldID = env->GetFieldID(classID, fieldRefCache[i].fieldName, fieldRefCache[i].fieldSignature);
		i++;
	}

	return JNI_VERSION_1_2;
}

void RefCache::tearDown(JNIEnv *env) {
	int i=0;
	while (classRefCache[i].className != NULL) {
		if (classRefCache[i].classID != NULL) {
			env->DeleteWeakGlobalRef(classRefCache[i].classID);
			classRefCache[i].classID = NULL;
		}
		i++;
	}
}
