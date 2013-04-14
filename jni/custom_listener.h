//
//  custom_listener.h
//  AnotherSocketClient
//
//  Created by Genesislive on 1/30/13.
//  Copyright (c) 2013 Genesislive. All rights reserved.
//
#ifndef _CUSTOM_LISTENER_H_
#define _CUSTOM_LISTENER_H_
#if BUILDING_DLL
# define DLLIMPORT __declspec (dllexport)
#else /* Not BUILDING_DLL */
# define DLLIMPORT __declspec (dllimport)
#endif /* Not BUILDING_DLL */

#ifndef __AnotherSocketClient__custom_listener__
#define __AnotherSocketClient__custom_listener__

#include <iostream>
#include "client_listener.h"
#include "log_c.h"
#include "socket_client.h"
#define successfully_connected_to_server 1
#define connection_is_closed 2
#define failed_to_create_socket 3
#define max_retry_exceed 4
#define couldnot_connected_to_server 5
#define send_data_to_server_failed 6
#define failed_to_recv_data_from_server 7


class custom_listener : public client_listener {
public:
    custom_listener() {}
    ~custom_listener() {}
    
    virtual void conn_status_changed(socket_client *pSocketClient, int status);
    virtual void post_message(socket_client *pSocketClient, int report);
    virtual void data_received(socket_client *pSocketClient, char *data, long len);
};

#endif /* defined(__AnotherSocketClient__custom_listener__) */
#endif 
