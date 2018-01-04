#include <stdio.h>
#include <jni.h>
#include "org_px5_io_BTJoystick.h"

JNIEXPORT void JNICALL Java_org_px5_io_BTJoystick_jsInput (JNIEnv *, jobject) {
	printf("hello jni\n");
	return;
}
