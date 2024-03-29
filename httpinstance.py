from http.server import BaseHTTPRequestHandler, SimpleHTTPRequestHandler, HTTPServer
import socketserver
import httpserver

HOSTNAME = "localhost"
PORT_NUMBER = 9000

handler = httpserver.My_HTTP_Handler
httpd = HTTPServer((HOSTNAME, PORT_NUMBER), handler)
print(f"Serving on port {PORT_NUMBER}")
httpd.serve_forever()
