//
//  client_listener.h
//  AnotherSocketClient
//
//  Created by Genesislive on 1/30/13.
//  Copyright (c) 2013 Genesislive. All rights reserved.
//

#ifndef __AnotherSocketClient__client_listener__
#define __AnotherSocketClient__client_listener__

#include <iostream>
#include <string>
class socket_client;
class client_listener {
public:
    client_listener() {}
    virtual ~client_listener() {}
    
    virtual void conn_status_changed(socket_client *pSocketClient, int status) = 0;
    virtual void post_message(socket_client *pSocketClient, int report) = 0;
    virtual void data_received(socket_client *pSocketClient, char *data, long len) = 0;
};

#endif /* defined(__AnotherSocketClient__client_listener__) */
