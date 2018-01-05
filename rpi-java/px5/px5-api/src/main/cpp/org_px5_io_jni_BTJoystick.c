#include <stdio.h>
#include <jni.h>
#include "org_px5_io_jni_BTJoystick.h"
#include "controller.h"

JNIEXPORT jint JNICALL Java_org_px5_io_jni_BTJoystick_jsInput
  (JNIEnv * env, jobject obj, jint in){
	printf("in c, get %d\n", in);
}

JNIEXPORT jint JNICALL Java_org_px5_io_jni_BTJoystick_jsQuery
(JNIEnv * env, jobject obj){
	int len = 0;
	Controller controller;
	while (1){
		//printf("before\n");
		//block until new event
		len = controller.xbox_map_read();
		//printf("after\n");
		if (len < 0)
		{
			//should never be here
			printf("!!!\n");
			usleep(1000 * 1000);
			continue;
		}
		//printf("123");
	}
}

JNIEXPORT void JNICALL Java_org_px5_io_jni_BTJoystick_init
  (JNIEnv * env, jobject obj, jstring callbackName, jstring callbackSignature){

}
