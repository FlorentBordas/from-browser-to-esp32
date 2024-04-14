import http.server
from http.server import BaseHTTPRequestHandler, SimpleHTTPRequestHandler, HTTPServer
import socketserver
import impl_server
import database as db
import client_mqtt_rasp as cl
import threading

HOSTNAME = ""
PORT_NUMBER = 9000

db.open_data()

handler = impl_server.My_HTTP_Handler
httpd = http.server.HTTPServer((HOSTNAME, PORT_NUMBER), handler)
print(f"Serving on port {PORT_NUMBER}")

mqtt_thread = threading.Thread(target=cl.start_mqtt_client)
mqtt_thread.daemon = True 
mqtt_thread.start()

httpd.serve_forever()