/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_jxpcap_Writer */

#ifndef _Included_com_jxpcap_Writer
#define _Included_com_jxpcap_Writer
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_jxpcap_Writer
 * Method:    nativeOpenDumpFile
 * Signature: (JLjava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_jxpcap_Writer_nativeOpenDumpFile
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     com_jxpcap_Writer
 * Method:    nativeWritePacket
 * Signature: (Lcom/jxpcap/packet/Packet;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_jxpcap_Writer_nativeWritePacket
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif