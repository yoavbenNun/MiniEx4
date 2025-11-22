#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {
    // Define target server IP (localhost) and port
    const char* ip_address = "127.0.0.1";
    const int port_no = 5555;

    // 1. Create the socket
    // AF_INET = IPv4, SOCK_STREAM = TCP
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    // 2. Define the server address structure to connect to
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address); // Convert IP string to network address
    sin.sin_port = htons(port_no);

    // 3. Establish a connection to the server (3-way handshake)
    if (connect(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error connecting to server");
    }

    // 4. Send a message to the server
    // Using the modified message string as requested in the exercise
    char data_addr[] = "Yoav TCP final Test!"; 
    int data_len = strlen(data_addr);
    int sent_bytes = send(sock, data_addr, data_len, 0);

    if (sent_bytes < 0) {
        // error handling
    }

    // 5. Receive the response from the server
    char buffer[4096];
    int expected_data_len = sizeof(buffer);
    int read_bytes = recv(sock, buffer, expected_data_len, 0);
    
    // Handle response
    if (read_bytes == 0) {
        // connection is closed
    }
    else if (read_bytes < 0) {
        // error
    }
    else {
        // Print the server's response
        cout << buffer;
    }

    // 6. Close the socket
    close(sock);


    return 0;
}