#include <pcap.h>
#include <jni.h>
#include <unistd.h>
#include "util.h"

jlong toJlong(void *ptr) {
#ifndef WIN32
    jlong lp = (intptr_t) ptr;
#else
    jlong lp = (UINT_PTR) ptr;
#endif
    return lp;
}

void *toPtr(jlong lp) {
#ifndef WIN32
    void *ptr = (void *) ((intptr_t) lp);
#else
    void *ptr = (void *) ((UINT_PTR) lp);
#endif
    return ptr;
}

pcap_t *getPcap(jlong lp) {
    return ((pcap_t *) toPtr(lp));
}

pcap_dumper_t *getPcapDumper(jlong lp) {
	return ((pcap_dumper_t *) toPtr(lp));
}

void setPcap(JNIEnv *env, jobject jobj, jfieldID FID, pcap_t *pcap) {
	(*env)->SetLongField(env, jobj, FID, toJlong(pcap));
}

void setPcapDumper(JNIEnv *env, jobject jobj, jfieldID FID, pcap_dumper_t *pcap_dumper) {
	(*env)->SetLongField(env, jobj, FID, toJlong(pcap_dumper));
}

void setMsg(JNIEnv *env, jobject jobj, const char *message) {
    jclass Message = (*env)->FindClass(env, "com/jxpcap/util/Message");
    jmethodID set_message_MID = (*env)->GetMethodID(env, Message, "setMessage", "(Ljava/lang/String;)V");
    if(message == NULL) {
		message = "";
	}
    jstring jstr = (*env)->NewStringUTF(env, message);
    (*env)->CallVoidMethod(env, jobj, set_message_MID, jstr);
    return;
}