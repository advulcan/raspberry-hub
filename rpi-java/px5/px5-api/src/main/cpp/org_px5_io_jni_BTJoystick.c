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
		/*len = controller.xbox_map_read();
		//printf("after\n");
		if (len < 0)
		{
			//should never be here
			printf("!!!\n");
			usleep(1000 * 1000);
			continue;
		}*/
		int * result = controller.xbox_event_read();
		//printf("123");
	}
}
Controller controller;
JNIEXPORT jintArray JNICALL Java_org_px5_io_jni_BTJoystick_readEvent
(JNIEnv * env, jobject obj){
	int * result = controller.xbox_event_read();
	int eventArrayLen = 4;
	jintArray jint_arr_temp = env->NewIntArray(eventArrayLen);
	//jint* int_arr_temp = env->GetIntArrayElements(jint_arr_temp,NULL);
	//printf("readed(%d,%d,%d,%d)\n",result[0],result[1],result[2],result[3]);
	env->SetIntArrayRegion(jint_arr_temp, 0, eventArrayLen, result);
	delete []result;
	return jint_arr_temp;
}
JNIEXPORT void JNICALL Java_org_px5_io_jni_BTJoystick_init
  (JNIEnv * env, jobject obj, jstring callbackName, jstring callbackSignature){

}
