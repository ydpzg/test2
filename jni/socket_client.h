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
    int retry_timeout;      // 连接超时
    int retry_count;        // 重试次数
} client_settings;

typedef struct {
    std::string server;     // 服务器地址
    int port;               // 服务器端口
} conn_params;

typedef struct {
    char *buffer;           // 具体缓冲内容
    int len;                // 缓冲区内容长度
    int timeout;            // 超时（以毫秒为单位）
} buffer_item;



class socket_client {
public:
    socket_client(client_settings settings, client_listener *listener);
    ~socket_client();
    
    bool async_connect_retry(std::string server, int port);         // 连接至服务器
    bool connect_to_server(std::string server, int port);
    void close_connection();                                        // 断开到服务器的连接
    bool is_connected();
    
    void send_data(char *data, int length, int timeout);            // 发送数据
	
	std::string get_server_addr();
    int get_server_port();
    
private:
    int get_client_socket();
    void set_connected(bool conn);
    
    bool is_send_available();
    buffer_item get_next_pending_buffer();                          // 获取下一个待发送的缓冲区
    
    int get_conn_retry_count();                                     // 重连次数
    
    
    pthread_mutex_t *get_send_mutex();                              // 同步
    pthread_mutex_t *get_recv_mutex();
    pthread_cond_t *get_send_cond();
    pthread_cond_t *get_response_cond();
    
    void post_error(int error);
    void post_data(char *data, long len);
    void conn_status_changed(int status);                   // 回调
    
private:
    static void *connect_retry(void *arg);
    static void *send_handler(void *arg);
    static void *recv_handler(void *arg);
    
private:
    client_settings setting;                    // 用户设置
    conn_params conn_param;                     // 连接配置
    
    bool connected;
    
    concurrent_queue<buffer_item> buffers;      // 本地缓冲
    char *recv_data_buffer;
    
    int client_socket;                          // Socket 通讯
    std::string server_address;
    int server_port;
    
    pthread_t conn_thread;
    pthread_t send_thread;                      // 用于发送和接收数据的线程
    pthread_t recv_thread;
    
    pthread_mutex_t mutex;                      // 用于同步的锁和条件变量
    pthread_mutex_t send_data_mutex;
    pthread_mutex_t recv_data_mutex;
    
    pthread_cond_t data_available_cond;
    pthread_cond_t response_available;
    
    client_listener *callback;                  // 回调
};

#endif /* defined(__AnotherSocketClient__socket_client__) */


