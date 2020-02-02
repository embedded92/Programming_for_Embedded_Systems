#include <stdlib.h>
#include <stdio.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main()
{
    char server_msg[256] = "Message from server";
    
    // create a server socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // define the server address
    struct sockaddr_in server_address;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);

    //bind the server to specific ip and port
    bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    while(1)
    {
        // start lisening for connections
        listen(server_socket, 10);

        int client_socket;
        client_socket = accept(server_socket, NULL, NULL);

        //send the message
        send(client_socket, server_msg, sizeof(server_msg), 0);
    }
    return 0;
}