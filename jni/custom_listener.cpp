//
//  custom_listener.cpp
//  AnotherSocketClient
//
//  Created by Genesislive on 1/30/13.
//  Copyright (c) 2013 Genesislive. All rights reserved.
//

#include "custom_listener.h"
#include <iostream>

void custom_listener::conn_status_changed(socket_client *pSocketClient, int status)
{	
	if(status == successfully_connected_to_server) {
		std::cout << "calling custom conn_status_changed\n\t" << "successfully_connected_to_server" << std::endl;
		LOGI("calling custom conn_status_changed = successfully_connected_to_server");
	} else if(status == connection_is_closed){
		std::cout << "calling custom conn_status_changed\n\t" << "connection_is_closed" << std::endl;
		LOGI("calling custom conn_status_changed = connection_is_closed");
	}
}

void custom_listener::post_message(socket_client *pSocketClient, int report)
{	
    //std::cout << "calling custom post_message\n\t" << report << std::endl;
	LOGI("calling custom post_message = %d", report);
}

void custom_listener::data_received(socket_client *pSocketClient, char *data, long len)
{	

    std::cout << "calling custom data_received\n\t" << len << " bytes received." << std::endl;
	LOGI("calling custom data_received %d byte.data = %s-->%s-->%d", len, data, pSocketClient->get_server_addr().c_str(), pSocketClient->get_server_port());
}



