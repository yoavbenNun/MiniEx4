#include <iostream>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main() {

    const char* ip_address = "127.0.0.1";
    const int port_no = 5555;

    // Create a UDP socket
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }

    // Define the destination server address
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address); // Convert IP string to address
    sin.sin_port = htons(port_no);

    // Data to send
    // Note: If you changed this to "Test C++ UDP", keep your change here!
    //original : char data[] = "hello";
    // my change : change the message content to verify dynamic echo
    char data[] = "Test C++ UDP";
    int data_len = sizeof(data);

    // Send the data to the server using sendto (no connection needed for UDP)
    int sent_bytes = sendto(sock, data, data_len, 0, (struct sockaddr *) &sin, sizeof(sin));
    if (sent_bytes < 0) {
        perror("error writing to socket");
    }

    // Prepare to receive the response
    struct sockaddr_in from;
    unsigned int from_len = sizeof(struct sockaddr_in);
    char buffer[4096];

    // Receive the response from the server
    int bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &from, &from_len);
    if (bytes < 0) {
        perror("error reading from socket");
    }

    // Print the server's response
    cout << "The server sent: " << buffer << endl;

    close(sock);

    return 0;
}