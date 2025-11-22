# Import necessary socket modules
from socket import socket, AF_INET, SOCK_DGRAM

# Create a UDP socket using IPv4 addressing
s = socket(AF_INET, SOCK_DGRAM)

# Define the destination IP (localhost)
dst_ip = '127.0.0.1'
# Define the destination port matching the server
dst_port = 12345

# Send a message 'Hello' (as bytes) to the server's address
s.sendto(b'Hello', (dst_ip,dst_port))

# Wait to receive a response (up to 2048 bytes) from the server
data, sender_info = s.recvfrom(2048)
# Decode the response to a string and print it
print(data.decode('utf-8'))
# Print the server's address info
print(sender_info)

# Close the socket to release resources
s.close()