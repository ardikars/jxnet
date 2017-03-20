/**
 * Copyright (C) 2017  Ardika Rommy Sanjaya
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <jni.h>
#include <pcap.h>
#include <dnet.h>
#include <sys/time.h>

#include "ids.h"
#include "utils.h"

#ifdef WIN32
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <iphlpapi.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif

void swap_order_uint32(uint32_t *value) {
	*value = ((*value << 8) & 0xFF00FF00 ) | ((*value >> 8) & 0xFF00FF); 
	*value = (*value << 16) | (*value >> 16);
}

void ThrowNew(JNIEnv *env, const char *class_name, const char *message) {
	(*env)->ThrowNew(env, (*env)->FindClass(env, class_name), message);
}

jlong PointerToJlong(void *pointer) {
	jlong address = 0;
#ifndef WIN32
    address = (intptr_t) pointer;
#else
    address = (UINT_PTR) pointer;
#endif
    return address;
}

void *JlongToPointer(jlong address) {
	void *pointer = NULL;
#ifndef WIN32
    pointer = (void *) ((intptr_t) address);
#else
    pointer = (void *) ((UINT_PTR) address);
#endif
    return pointer;
}


void SetStringBuilder(JNIEnv *env, jobject obj, const char *str) {
	if(obj == NULL) {
		ThrowNew(env, NULL_PTR_EXCEPTION, NULL);
	}
	SetStringBuilderIDs(env);
	(*env)->CallVoidMethod(env, obj, StringBuilderSetLengthMID, (jint) 0);
	(*env)->CallObjectMethod(env, obj, StringBuilderAppendMID, (*env)->NewStringUTF(env, str));
}

jobject NewObject(JNIEnv *env, jclass class, const char *name, const char *signature) {
	return (*env)->NewObject(env, class, (*env)->GetMethodID(env, class, name, signature));
}

jbyteArray NewByteAddr(JNIEnv *env, struct sockaddr *addr) {
	if(addr==NULL) { 
		return NULL;
	}
	jbyteArray address = NULL;
	switch(addr->sa_family){
		case AF_INET:
			address = (*env)->NewByteArray(env, 4);
			(*env)->SetByteArrayRegion(env, address, 0, 4, (jbyte *) & ((struct sockaddr_in *) addr)->sin_addr);
			break;
		case AF_INET6:
			address=(*env)->NewByteArray(env,16);
			(*env)->SetByteArrayRegion(env, address, 0, 16, (jbyte *) & ((struct sockaddr_in6 *) addr)->sin6_addr);
			break;
		default:
			return NULL;
			break;
	}
	return address;
}

jobject NewSockAddr(JNIEnv *env, struct sockaddr *addr) {
	jobject sockaddr = NewObject(env, SockAddrClass, "<init>", "()V");
	if(addr == NULL) {
		return sockaddr;
	}
	(*env)->SetShortField(env, sockaddr, SockAddrSaFamilyFID, (jshort) addr->sa_family);
	(*env)->SetObjectField(env, sockaddr, SockAddrDataFID, NewByteAddr(env, addr));
	return sockaddr;
}

jobject SetPcap(JNIEnv *env, pcap_t *pcap) {
	SetPcapIDs(env);
	jobject obj = NewObject(env, PcapClass, "<init>", "()V");
  	(*env)->SetLongField(env, obj, PcapAddressFID, PointerToJlong(pcap));
  	return obj;
}

jobject SetArp(JNIEnv *env, arp_t *arp) {
	SetArpIDs(env);
	jobject obj = NewObject(env, ArpClass, "<init>", "()V");
  	(*env)->SetLongField(env, obj, ArpAddressFID, PointerToJlong(arp));
  	return obj;
}

pcap_t *GetPcap(JNIEnv *env, jobject jpcap) {
	if(jpcap == NULL) {
		ThrowNew(env, NULL_PTR_EXCEPTION, NULL);
		return NULL;
	}
	SetPcapIDs(env);
	jlong pcap = 0;
	if ((pcap = (*env)->GetLongField(env, jpcap, PcapAddressFID)) == 0) {
		ThrowNew(env, PCAP_CLOSE_EXCEPTION, NULL);
	}
	return JlongToPointer(pcap);
}

arp_t *GetArp(JNIEnv *env, jobject jarp) {
	if(jarp == NULL) {
		ThrowNew(env, NULL_PTR_EXCEPTION, NULL);
		return NULL;
	}
	SetArpIDs(env);
	jlong arp = 0;
	if ((arp = (*env)->GetLongField(env, jarp, ArpAddressFID)) == 0) {
		ThrowNew(env, ARP_CLOSE_EXCEPTION, NULL);
	}
	return JlongToPointer(arp);
}

jobject SetFile(JNIEnv *env, FILE *file) {
	SetFileIDs(env);
	jobject obj = NewObject(env, FileClass, "<init>", "()V");
  	(*env)->SetLongField(env, obj, FileAddressFID, PointerToJlong(file));
  	return obj;
}

FILE *GetFile(JNIEnv *env, jobject jf) {
	if(jf == NULL) {
		ThrowNew(env, NULL_PTR_EXCEPTION, NULL);
		return NULL;
	}
	SetFileIDs(env);
	jlong file = 0;
	if ((file = (*env)->GetLongField(env, jf, FileAddressFID)) == 0) {
		ThrowNew(env, FILE_CLOSE_EXCEPTION, NULL);
	}
	return JlongToPointer(file);
}

jobject SetPcapDumper(JNIEnv *env, pcap_dumper_t *pcap_dumper) {
	SetPcapDumperIDs(env);
	jobject obj = NewObject(env, PcapDumperClass, "<init>", "()V");
  	(*env)->SetLongField(env, obj, PcapDumperAddressFID, PointerToJlong(pcap_dumper));
  	return obj;
	
}

pcap_dumper_t *GetPcapDumper(JNIEnv *env, jobject jpcap_dumper) {
	if(jpcap_dumper == NULL) {
		ThrowNew(env, NULL_PTR_EXCEPTION, NULL);
		return NULL;
	}
	SetPcapDumperIDs(env);
	jlong pcap_dumper = 0;
	if ((pcap_dumper = (*env)->GetLongField(env, jpcap_dumper, PcapDumperAddressFID)) == 0) {
		ThrowNew(env, PCAP_DUMPER_CLOSE_EXCEPTION, NULL);
	}
	return JlongToPointer(pcap_dumper);
}

jobject SetBpfProgram(JNIEnv *env, jobject obj, struct bpf_program *fp) {
	SetBpfProgramIDs(env);
  	(*env)->SetLongField(env, obj, BpfProgramAddressFID, PointerToJlong(fp));
  	return obj;
}

struct bpf_program *GetBpfProgram(JNIEnv *env, jobject jbpf_program) {
	if(jbpf_program == NULL) {
		ThrowNew(env, NULL_PTR_EXCEPTION, NULL);
		return NULL;
	}
	SetBpfProgramIDs(env);
	jlong bpf_program = 0;
	if ((bpf_program = (*env)->GetLongField(env, jbpf_program, BpfProgramAddressFID)) == 0) {
		ThrowNew(env, BPF_PROGRAM_CLOSE_EXCEPTION, NULL);
	}
	return JlongToPointer(bpf_program);
	
}

void pcap_callback(u_char *user, const struct pcap_pkthdr *pkt_header, const u_char *pkt_data) {
	pcap_user_data_t *user_data = (pcap_user_data_t *) user;
	JNIEnv *env = user_data->env;
	jobject pkt_hdr = NewObject(env, PcapPktHdrClass, "<init>", "()V");
	(*env)->SetIntField(env, pkt_hdr, PcapPktHdrCaplenFID, (jint) pkt_header->caplen);
	(*env)->SetIntField(env, pkt_hdr, PcapPktHdrLenFID, (jint) pkt_header->len);
	(*env)->SetIntField(env, pkt_hdr, PcapPktHdrTvSecFID, (jint) pkt_header->ts.tv_sec);
	(*env)->SetLongField(env, pkt_hdr, PcapPktHdrTvUsecFID, (jlong) pkt_header->ts.tv_usec);
	(*env)->CallNonvirtualVoidMethod(env,
    			user_data->callback,
			user_data->PcapHandlerClass,
			user_data->PcapHandlerNextPacketMID,
			user_data->user,
			pkt_hdr,
			(*env)->NewDirectByteBuffer(env, (void *) pkt_data, (jint) pkt_header->caplen));
	(*env)->DeleteLocalRef(env, pkt_hdr);
}

int arp_callback(const struct arp_entry *entry, void *arg) {
	jbyteArray jb = NULL;
	arp_user_data_t *user_data = (arp_user_data_t *) arg;
	JNIEnv *env = user_data->env;

	jb = (*env)->NewByteArray(env, 4);
	(*env)->SetByteArrayRegion(env, jb, 0, 4, (jbyte *) &entry->arp_pa.addr_data8);
	jobject addr_pa = (*env)->CallStaticObjectMethod(env, AddrClass, AddrInitializeMID,
			 entry->arp_pa.addr_type, entry->arp_pa.addr_bits, jb);
	if (addr_pa == NULL) {
		return -1;
	}
	jb = (*env)->NewByteArray(env, 6);
	(*env)->SetByteArrayRegion(env, jb, 0, 6, (jbyte *) &entry->arp_ha.addr_data8);
	jobject addr_ha = (*env)->CallStaticObjectMethod(env, AddrClass, AddrInitializeMID,
			 entry->arp_ha.addr_type, entry->arp_ha.addr_bits, jb);
	if (addr_ha == NULL) {
		return -1;
	}
	jobject arp_entry = (*env)->CallStaticObjectMethod(env, ArpEntryClass, ArpEntryInitializeMID,
			addr_pa, addr_ha);
	if (arp_entry == NULL) {
		return -1;
	}
	int res = (*env)->CallNonvirtualIntMethod(env,
			user_data->callback,
			user_data->ArpHandlerClass,
			user_data->ArpHandlerNextArpEntryMID,
			arp_entry,
			user_data->user);
	(*env)->DeleteLocalRef(env, addr_pa);
	(*env)->DeleteLocalRef(env, addr_ha);
	(*env)->DeleteLocalRef(env, arp_entry);
	return res;
}
