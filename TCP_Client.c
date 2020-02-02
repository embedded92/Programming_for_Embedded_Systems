#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>


int main()
{
    // create a socket 
    int network_socket;
    /*
    * in params : 
    * domain : address family (AF_INET = ipv4)
    * type : type of socket (SOCK_STREAM = conection oriented)
    * protocol : 0 (IP protocol)
    * 
    * out params : 
    * descriptor of the socket
    */
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // specify an address for the socket
    struct sockaddr_in server_addr;
    server_addr.sin_addr.s_addr = INADDR_ANY;       // ipaddr for local host similar to 0.0.0.0
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);       // convert integer port number to correct byte order for network

    // connect to the socket
    int connection_status = connect(network_socket, (struct sockaddr*)&server_addr, sizeof(server_addr) );
    if (connection_status == -1)
    {
        printf("Failed to connect to socket \n\r");
    }

    // recieve data from the server
    char server_data[256];
    recv(network_socket, &server_data, sizeof(server_data), 0);

    // printout the data recieved from the server reponse
    printf(" data recieved from server : %s \r\n", server_data);

    //close the connection
    //close(network_socket);

    return 0;
}