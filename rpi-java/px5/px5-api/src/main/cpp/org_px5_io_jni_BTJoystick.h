/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_px5_io_jni_BTJoystick */

#ifndef _Included_org_px5_io_jni_BTJoystick
#define _Included_org_px5_io_jni_BTJoystick
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_px5_io_jni_BTJoystick
 * Method:    jsInput
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_org_px5_io_jni_BTJoystick_jsInput
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_px5_io_jni_BTJoystick
 * Method:    jsQuery
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_px5_io_jni_BTJoystick_jsQuery
  (JNIEnv *, jobject);

/*
 * Class:     org_px5_io_jni_BTJoystick
 * Method:    init
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_px5_io_jni_BTJoystick_init
  (JNIEnv *, jobject, jstring, jstring);

#ifdef __cplusplus
}
#endif
#endif
