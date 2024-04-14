import http.server
from http.server import BaseHTTPRequestHandler, SimpleHTTPRequestHandler, HTTPServer
import socketserver
import impl_server
import database as db

HOSTNAME = ""
PORT_NUMBER = 9000

db.open_data()
handler = impl_server.My_HTTP_Handler
httpd = http.server.HTTPServer((HOSTNAME, PORT_NUMBER), handler)
print(f"Serving on port {PORT_NUMBER}")
httpd.serve_forever()
