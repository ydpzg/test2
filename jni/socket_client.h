//
//  socket_client.h
//  AnotherSocketClient
//
//  Created by Genesislive on 1/30/13.
//  Copyright (c) 2013 Genesislive. All rights reserved.
//

#ifndef __AnotherSocketClient__socket_client__
#define __AnotherSocketClient__socket_client__

#include "iostream"

#include <pthread.h>
#include <sys/socket.h>
#include <string.h>
#include "concurrent_queue.hpp"
#include "custom_listener.h"
#include "common.h"
#include "log_c.h"




typedef struct {
    int retry_timeout;      // ���ӳ�ʱ
    int retry_count;        // ���Դ���
} client_settings;

typedef struct {
    std::string server;     // ��������ַ
    int port;               // �������˿�
} conn_params;

typedef struct {
    char *buffer;           // ���建������
    int len;                // ���������ݳ���
    int timeout;            // ��ʱ���Ժ���Ϊ��λ��
} buffer_item;



class socket_client {
public:
    socket_client(client_settings settings, client_listener *listener);
    ~socket_client();
    
    bool async_connect_retry(std::string server, int port);         // ������������
    bool connect_to_server(std::string server, int port);
    void close_connection();                                        // �Ͽ���������������
    bool is_connected();
    
    void send_data(char *data, int length, int timeout);            // ��������
	
	std::string get_server_addr();
    int get_server_port();
    
private:
    int get_client_socket();
    void set_connected(bool conn);
    
    bool is_send_available();
    buffer_item get_next_pending_buffer();                          // ��ȡ��һ�������͵Ļ�����
    
    int get_conn_retry_count();                                     // ��������
    
    
    pthread_mutex_t *get_send_mutex();                              // ͬ��
    pthread_mutex_t *get_recv_mutex();
    pthread_cond_t *get_send_cond();
    pthread_cond_t *get_response_cond();
    
    void post_error(int error);
    void post_data(char *data, long len);
    void conn_status_changed(int status);                   // �ص�
    
private:
    static void *connect_retry(void *arg);
    static void *send_handler(void *arg);
    static void *recv_handler(void *arg);
    
private:
    client_settings setting;                    // �û�����
    conn_params conn_param;                     // ��������
    
    bool connected;
    
    concurrent_queue<buffer_item> buffers;      // ���ػ���
    char *recv_data_buffer;
    
    int client_socket;                          // Socket ͨѶ
    std::string server_address;
    int server_port;
    
    pthread_t conn_thread;
    pthread_t send_thread;                      // ���ڷ��ͺͽ������ݵ��߳�
    pthread_t recv_thread;
    
    pthread_mutex_t mutex;                      // ����ͬ����������������
    pthread_mutex_t send_data_mutex;
    pthread_mutex_t recv_data_mutex;
    
    pthread_cond_t data_available_cond;
    pthread_cond_t response_available;
    
    client_listener *callback;                  // �ص�
};

#endif /* defined(__AnotherSocketClient__socket_client__) */


