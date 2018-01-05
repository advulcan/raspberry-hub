#include <stdio.h>
#include <jni.h>
#include "org_px5_io_jni_BTJoystick.h"

JNIEXPORT jint JNICALL Java_org_px5_io_jni_BTJoystick_jsInput
  (JNIEnv * env, jobject obj, jint in){
	printf("in c, get %d\n", in);
}

JNIEXPORT void JNICALL Java_org_px5_io_jni_BTJoystick_init
  (JNIEnv * env, jobject obj, jstring callbackName, jstring callbackSignature){

}
