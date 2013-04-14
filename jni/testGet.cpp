#include <string.h>
#include <string>
//#include <jni.h>
#include <stdio.h>
#include "socket_client.h"
#include "custom_listener.h"
//#include "client_listener.h"
//#include "common.h"
//#include "concurrent_queue.hpp"
#include <iostream>
#include "log_c.h"
#include "com_example_mytest0126_JNI.h"
using namespace std;

bool onStop = false;
socket_client* client;
socket_client* client1;
socket_client* client2;

int getData(int src) {
	return src;
}

jint Java_com_example_mytest0126_JNI_connect1(JNIEnv* env, jobject thiz,
		jint src) {
	if(client != NULL && client->is_connected()) {
		return 0;
	}
	client_settings settings;
	settings.retry_count = 0;
	settings.retry_timeout = 0;

	client_listener *listener = new custom_listener();

	client = new socket_client(settings, listener);


//	LOGI("程序正常运行");

//	if (client->connect_to_server("192.168.1.35", 4433)) {
//		LOGI("成功连接到服务器");
//	}
	if (client->async_connect_retry("192.168.1.35", 7881)) {
		LOGI("成功连接到服务器");
	}

	// client.async_connect_retry("127.0.0.1", 14250);

//	    while (!client.is_connected()) {
//	    }
//
//	    if (client.is_connected()) {
//	        printf("成功连接到服务器\n");
//	    }

	char buffer[1024] = "client is ready to send!";
	//FILE *file = fopen("input", "r");

	//if (!file) {
	//    printf("Couldn't open file");
	//}

	// while (!feof(file)) {
	//    fread(buffer, 1, 20, file);
	//    printf("send %s\n", buffer);
	//    client.send_data(buffer, 20, 0);
	// }
//	onStop = false;
//	client->send_data(buffer, strlen(buffer), 0);
	//LOGI("send_the_inf1:%s" , buffer);
//	client->send_data(buffer, 3, 1);

//	LOGI("connect_ok");
	return 111;

}
jint Java_com_example_mytest0126_JNI_connect2(JNIEnv* env, jobject thiz,
		jint src) {
	if(client2 != NULL && client2->is_connected()) {
			return 0;
		}
	client_settings settings2;
	settings2.retry_count = 0;
	settings2.retry_timeout = 0;

	client_listener *listener2 = new custom_listener();
	client2 = new socket_client(settings2, listener2);

//	LOGI("程序正常运行");

//	if (client->connect_to_server("192.168.1.35", 4433)) {
//		LOGI("成功连接到服务器");
//	}
	if (client2->async_connect_retry("192.168.1.35", 7880)) {
		LOGI("成功连接到服务器2");
	}

	// client.async_connect_retry("127.0.0.1", 14250);

//	    while (!client.is_connected()) {
//	    }
//
//	    if (client.is_connected()) {
//	        printf("成功连接到服务器\n");
//	    }

	char buffer[1024] = "client is ready to send!";
	//FILE *file = fopen("input", "r");

	//if (!file) {
	//    printf("Couldn't open file");
	//}

	// while (!feof(file)) {
	//    fread(buffer, 1, 20, file);
	//    printf("send %s\n", buffer);
	//    client.send_data(buffer, 20, 0);
	// }
//	onStop = false;
	//client2->send_data(buffer, strlen(buffer), 0);
	//LOGI("send_the_inf2:%s" , buffer);
//	client->send_data(buffer, 3, 1);

//	LOGI("connect_ok");

	return 111;

}
string jstring2str(JNIEnv* env, jstring jstr)
{
    char*   rtn   =   NULL;
    jclass   clsstring   =   env->FindClass("java/lang/String");
    jstring   strencode   =   env->NewStringUTF("GB2312");
    jmethodID   mid   =   env->GetMethodID(clsstring,   "getBytes",   "(Ljava/lang/String;)[B");
    jbyteArray   barr=   (jbyteArray)env->CallObjectMethod(jstr,mid,strencode);
    jsize   alen   =   env->GetArrayLength(barr);
    jbyte*   ba   =   env->GetByteArrayElements(barr,JNI_FALSE);
    if(alen   >   0)
    {
        rtn   =   (char*)malloc(alen+1);
        memcpy(rtn,ba,alen);
        rtn[alen]=0;
    }
    env->ReleaseByteArrayElements(barr,ba,0);
    std::string stemp(rtn);
    free(rtn);
    return   stemp;
}

void Java_com_example_mytest0126_JNI_sendToServer1(JNIEnv* env, jobject thiz, jstring inf) {
	string tempStr = jstring2str(env, inf);
	LOGI("send_the_inf1:%s" , tempStr.c_str());
	if(client != NULL) {
		client->send_data((char*)(tempStr.c_str()), strlen(tempStr.c_str()), 0);
	}
}
void Java_com_example_mytest0126_JNI_sendToServer2(JNIEnv* env, jobject thiz, jstring inf) {
	string tempStr = jstring2str(env, inf);
	if(client2 != NULL) {
		client2->send_data((char*)(tempStr.c_str()), strlen(tempStr.c_str()), 0);
	}
	LOGI("send_the_inf2:%s" , tempStr.c_str());
}

void Java_com_example_mytest0126_JNI_closeConnection1(JNIEnv* env, jobject thiz) {

	if(client != NULL) {
		client->close_connection();
		delete (client);
		client = NULL;
		LOGI("close_ok1");
	}
}
void Java_com_example_mytest0126_JNI_closeConnection2(JNIEnv* env, jobject thiz) {

	if(client2 != NULL) {
		client2->close_connection();
		delete (client2);
		client2 = NULL;
		LOGI("close_ok2");
	}
}

