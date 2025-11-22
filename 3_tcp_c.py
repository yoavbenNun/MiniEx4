# Import the socket module
import socket

# Create a TCP socket
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# Define server IP and port
dest_ip = '127.0.0.1'
dest_port = 12345
# Establish a connection to the server (Handshake)
s.connect((dest_ip, dest_port))

# Get input from the user
msg = input("Message to send: ")
# Loop until the user types 'quit'
while not msg == 'quit':
    # Send the message encoded as bytes
    s.send(bytes(msg, 'utf-8'))
    # Receive the response from the server
    data = s.recv(4096)
    # Print the server's response
    print("Server sent: ", data.decode('utf-8'))
    # Ask for the next message
    msg = input("Message to send: ")

# Close the connection
s.close()