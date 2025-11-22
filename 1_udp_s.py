# Import necessary socket modules: socket object, IP protocol (AF_INET), UDP protocol (SOCK_DGRAM)
from socket import socket, AF_INET, SOCK_DGRAM

# Create a UDP socket using IPv4 addressing
s = socket(AF_INET, SOCK_DGRAM)

# Define the source IP (empty string means listen on all available interfaces)
src_ip = ''
# Define the port number to listen on
src_port = 12345
# Bind the socket to the specific IP and port
s.bind((src_ip, src_port))

# Start an infinite loop to keep the server running
while True:
    # Receive data (up to 2048 bytes) and the sender's address info
    data, sender_info = s.recvfrom(2048)
    # Decode the received bytes to a string and print it
    print(data.decode('utf-8'))
    # Print the sender's IP and port
    print(sender_info)

    # Send the received data back to the sender, converted to uppercase (Echo)
    # origin : s.sendto(data.upper(), sender_info)
    # my change : instead of upper, we switch to lower
    s.sendto(data.lower(), sender_info)
