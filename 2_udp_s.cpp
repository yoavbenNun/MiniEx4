#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {

    const int server_port = 5555;

    // Create a UDP socket (SOCK_DGRAM) using IPv4 (AF_INET)
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    // Define the server address structure
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin)); // Zero out the structure
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY; // Listen on any network interface
    sin.sin_port = htons(server_port); // Set the port number

    // Bind the socket to the address and port
    if (bind(sock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
        perror("error binding to socket");
    }

    // Variables to store sender information and received data
    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[4096];

    // Receive data from a client
    // recvfrom fills the buffer and the 'from' structure with sender details
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }

    // Print the received message
    cout << "The client sent: " << buffer << endl;

    // Send the same data back to the client (Echo) using the 'from' address
    int sent_bytes = sendto(sock, buffer, bytes, 0, (struct sockaddr *) &from, sizeof(from));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }

    // Close the socket
    close(sock);

    return 0;
}