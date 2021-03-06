import socket
import tqdm
import os

SEPARATOR = "<SEPARATOR>"
BUFFER_SIZE = 4096 

host = "192.168.56.103"
port = 5001

# the name of file we want to send
filename = "testfile.txt"

# get the file size
filesize = os.path.getsize(filename)

# create the client socket
s = socket.socket()
print(f"[+] Connecting to {host}:{port}")
s.connect((host, port))
print("[+] Connected.")

# send the filename and filesize
s.send(f"{filename}{SEPARATOR}{filesize}".encode())
# start sending the file
progress = tqdm.tqdm(range(filesize), f"Sending {filename}", unit="B", unit_scale=True, unit_divisor=1024)
with open(filename, "rb") as f:
    while True:
        # read the bytes from the file
        bytes_read = f.read(BUFFER_SIZE)
        if not bytes_read:
            break
            
        # we use sendall to assure transimission in
        # busy networks
        s.sendall(bytes_read)
        # update the progress bar
        progress.update(len(bytes_read))

s.close()
