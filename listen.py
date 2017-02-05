#!/usr/bin/env python

import socket
#import requests
#import SocketServer
#import re

#from BaseHTTPServer import BaseHTTPRequestHandler

#Socket stuff
host = socket.gethostname()
port = 8000
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind((host, port))
sock.listen(1)

while True:
    csock, caddr = sock.accept()
    print("Connection from: " + caddr)
    sock.send("SAMPSON LIVES!!!")

    #request = csock.recv(1024)
    #print request
    #match = re.match()