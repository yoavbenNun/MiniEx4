# Import the socket module
import socket

# Create a TCP socket (SOCK_STREAM) using IPv4
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Define server IP (empty means all interfaces)
server_ip = ''
# Define server port
server_port = 12345
# Bind the socket to the address
server.bind((server_ip, server_port))
# Start listening for incoming connections (queue size 5)
server.listen(5)

# Infinite loop to accept clients
while True:
    # Accept a new connection. Returns a new socket for this client and their address
    client_socket, client_address = server.accept()
    # Print the client's address
    print('Connection from: ', client_address)
    # Receive data from the client (up to 1024 bytes)
    data = client_socket.recv(1024)
    
    # Loop as long as data is received (empty string means disconnect)
    while not data.decode('utf-8') == '':
        # Print the received message
        print('Received: ', data.decode('utf-8'))
        # Send response back (converted to uppercase)
        # Note: If you changed this to reverse the string, make sure to update the code/comment here!
        #original : client_socket.send(data.upper())
        #my change : instead of upperCase, we reverse the string. "hello" -> "olleh"
        reversed_msg = data.decode('utf-8')[::-1]
        client_socket.send(reversed_msg.encode('utf-8'))
        # Wait for next message from the same client
        data = client_socket.recv(1024)

    # Client disconnected
    print('Client disconnected')
    # Close the specific client socket
    client_socket.close()