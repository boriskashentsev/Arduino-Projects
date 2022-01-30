#!/usr/bin/python2

import BaseHTTPServer
import urllib
import serial

serialInterface = serial.Serial('/dev/ttyACM0', 19200, timeout=1)
serialInterface.reset_input_buffer()

def HandleUrlRequest(path):
    url = urllib.unquote(path).strip()
    if url[-1] in '0123456789':
        number = url[-1]
        serialInterface.write(number.encode('utf-8'))
        
def GetPage():
    return """<html><head><style>
            .button {display: block; width: 115px; height: 115px; background: #4E9CAF; padding: 10px;
                    text-align: center; border-radius: 5px; color: white; font-weight: bold;
                    line-height: 50px; margin: 25px}
            </style></head>
            <body><center>
            <a class='button' href='0'>1</a>
            <a class='button' href='1'>2</a>
            <a class='button' href='2'>3</a>
            <a class='button' href='3'>4</a>
            </center></body></html>"""

class HttpHandler(BaseHTTPServer.BaseHTTPRequestHandler):
    def do_GET(self):
        HandleUrlRequest(self.path)
        self.send_response( 200 )
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write(GetPage())

BaseHTTPServer.HTTPServer(("", 8080), HttpHandler).serve_forever()
