//
//  Server.hpp
//  Playground
//
//  Created by David Kopala on 7/23/17.
//  Copyright © 2017 David Kopala. All rights reserved.
//

#ifndef Server_h
#define Server_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <functional>
#include "List.h"

class Server
{
    
public:
    //Constructor - Creates server at the specified port
    Server(int port);
    //unused create function
    void create();
    //unused error handler
    static void sigchld_handler(int s);
    //function that listens for new connections
    static void *listening_handler(void *sockfd);
    //function that handles data from each connection
    static void *connection_handler(void *socket_desc);
    
    struct join_newconn {
        Server *ptr;
        int sockfd;
    };
    //groups data about each client
    struct ClientInfo {
        char *addr;
        int port;
        int fd;
    };
    //
    struct join_newmessage {
        Server *ptr;
        ClientInfo *data;
    };
    //data about the message that was received
    struct TCPMessage {
        ClientInfo *addr;
        char *message;
    };
    //unused struct - switched to the List.h stuff
    struct socketList {
        int sockfd;
        struct socketList *next;
    };
    
    //writes a message to all clients
    void writeToAll(char *message);
    //write a message a specific client
    void writeToClient(ClientInfo *client, char *msg);
    //write a message to multiple clients
    void writeToClients(List<ClientInfo> *w_clients, char *msg);
    //a list of all the clients
    static List<ClientInfo> *clients;
    //a list of all the messages received
    static List<TCPMessage> *messages;
    
    virtual void newConnectionCallback(ClientInfo *info);
    virtual void newMessageCallback(TCPMessage *message);
    virtual void clientDisconnected(ClientInfo *info);
    
private:
    void *get_in_addr(struct sockaddr *sa);
    //the port number
    static int p;
    
};

#endif /* Server_hpp */
