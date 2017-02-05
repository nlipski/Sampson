#!/usr/bin/env python

import socket
import urlparse
import json
import time
import mraa

#Pin definitions
P0 = mraa.Gpio(13)
P1 = mraa.Gpio(20)
P2 = mraa.Gpio(25)
P3 = mraa.Gpio(14)
P4 = mraa.Gpio(0)
P5 = mraa.Gpio(33)
P6 = mraa.Gpio(47)
P7 = mraa.Gpio(21)

P0.dir(mraa.DIR_OUT)
P1.dir(mraa.DIR_OUT)
P2.dir(mraa.DIR_OUT)
P3.dir(mraa.DIR_OUT)
P4.dir(mraa.DIR_OUT)
P5.dir(mraa.DIR_OUT)
P6.dir(mraa.DIR_IN)
P7.dir(mraa.DIR_IN)

#Socket stuff
port = 8000
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(("10.217.56.180", port))
sock.listen(1)

data = {"user": "john"}  #urlencode(dict(email='john')).encode('ascii')
data = json.dumps(data)
http_response_post = """\
HTTP/1.1 200 OK

{0}
"""

http_response_get = """\
HTTP/1.1 200 OK

{0}
"""

print("\nListening for connection on port " + str(port) + "...")

while True:
    csock, caddr = sock.accept()
    print("Connection from: " + str(caddr))
    req  = csock.recv(1024)
    if req:
        print(req)
        if 'GET' in req:
            #Arduino listen
            #P0.write(1)
            #P1.write(1)
            #P2.write(1)
            #P3.write(1)
            #P4.write(1)
            #P5.write(1)
            time.sleep(1)

            data = json.dumps({'left': 4})
            print(data)
            csock.sendall(http_response_get.format(data))
        elif 'POST' in req:
            #P0.write(1)
            #P1.write(1)
            #P2.write(1)
            #P3.write(1)
            #P4.write(1)
            #P5.write(0)
            time.sleep(1)

            req_obj = req.strip('\r\n')
            req_obj = req_obj.split('\n')[-1]
            req_obj = dict(urlparse.parse_qsl(req_obj))
            id = int(req_obj['pill'])
            num = int(req_obj['dosage'])
            print id, num

            #logic for sched
            #if(id%2 != 0):
            #   P0.write(1)
            #else:
            #   P0.write(0)
            #if(id > 1):
            #   P1.write(1)
            #else:
            #   P1.write(0)
            #if(num%2 != 0):
            #   P2.write(1)
            #else:
            #   P2.write(0)
            #if(num == 2 or num == 3 or num == 6 or num == 7):
            #   P3.write(1)
            #else:
            #   P3.write(0)
            #if(num > 3):
            #   P4.write(1)
            #else:
            #   P4.write(0)
            csock.sendall(http_response_post)
        csock.close()