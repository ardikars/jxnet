/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_ardikars_jxpcap_Jxpcap */

#ifndef _Included_com_ardikars_jxpcap_Jxpcap
#define _Included_com_ardikars_jxpcap_Jxpcap
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_ardikars_jxpcap_Jxpcap
 * Method:    initIDs
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_ardikars_jxpcap_Jxpcap_initIDs
  (JNIEnv *, jclass);

/*
 * Class:     com_ardikars_jxpcap_Jxpcap
 * Method:    nativeOpenLive
 * Signature: (Ljava/lang/String;IIILjava/lang/StringBuilder;)Lcom/ardikars/jxpcap/Jxpcap;
 */
JNIEXPORT jobject JNICALL Java_com_ardikars_jxpcap_Jxpcap_nativeOpenLive
  (JNIEnv *, jclass, jstring, jint, jint, jint, jobject);

/*
 * Class:     com_ardikars_jxpcap_Jxpcap
 * Method:    nativeFindAllDevs
 * Signature: (Ljava/util/List;Ljava/lang/StringBuilder;)I
 */
JNIEXPORT jint JNICALL Java_com_ardikars_jxpcap_Jxpcap_nativeFindAllDevs
  (JNIEnv *, jclass, jobject, jobject);

/*
 * Class:     com_ardikars_jxpcap_Jxpcap
 * Method:    nativeSendPacket
 * Signature: (Lcom/ardikars/jxpcap/Jxpcap;Ljava/nio/ByteBuffer;I)I
 */
JNIEXPORT jint JNICALL Java_com_ardikars_jxpcap_Jxpcap_nativeSendPacket
  (JNIEnv *, jclass, jobject, jobject, jint);

/*
 * Class:     com_ardikars_jxpcap_Jxpcap
 * Method:    nativeLookupDev
 * Signature: (Ljava/lang/StringBuilder;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_ardikars_jxpcap_Jxpcap_nativeLookupDev
  (JNIEnv *, jclass, jobject);

/*
 * Class:     com_ardikars_jxpcap_Jxpcap
 * Method:    nativeGetErr
 * Signature: (Lcom/ardikars/jxpcap/Jxpcap;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_ardikars_jxpcap_Jxpcap_nativeGetErr
  (JNIEnv *, jclass, jobject);

/*
 * Class:     com_ardikars_jxpcap_Jxpcap
 * Method:    nativeClose
 * Signature: (Lcom/ardikars/jxpcap/Jxpcap;)V
 */
JNIEXPORT void JNICALL Java_com_ardikars_jxpcap_Jxpcap_nativeClose
  (JNIEnv *, jclass, jobject);

#ifdef __cplusplus
}
#endif
#endif
