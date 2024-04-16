from http.server import BaseHTTPRequestHandler
import json
import os
import mimetypes
from client_mqtt_rasp import send_esp32
import database as db


class My_HTTP_Handler(BaseHTTPRequestHandler):
    def handle_http(self, status, content_type):
        self.send_response(status)
        self.send_header("Content-type", content_type)
        self.end_headers()

    def do_POST(self):
        self.handle_data_exchange()

    def do_GET(self):
        if self.path.startswith("/request"):
            self.handle_data_exchange()
        else:
            self.handle_static()

    def handle_data_exchange(self):
        match self.path:
            case "/input_user":
                data = self.read_json()
                send_esp32(data["topic"], data["val"])
                self.send_json(data)

            case "/request_user/send_button_1":
                data = db.fetch_data("send_button_1")
                self.send_json(data)

            case "/request_user/send_button_2":
                data = db.fetch_data("send_button_2")
                self.send_json(data)
            case "/request_user/send_photoresistance_1":
                data = db.fetch_data("send_photoresistance_1")
                self.send_json(data)
            case "/request_user/send_photoresistance_2":
                data = db.fetch_data("send_photoresistance_2")
                self.send_json(data)
            case _:
                self.handle_http(404, "text/html")

    def handle_static(self):
        if self.path == "/":
            file_path = "static/index.html"
        else:
            file_path = "static" + self.path

        if os.path.exists(file_path):
            mime_type, _ = mimetypes.guess_type(file_path)
            if mime_type == None:
                mime_type = "application/byte-stream"
            self.handle_http(200, mime_type)

            with open(file_path, "rb") as file:
                self.wfile.write(file.read())
        else:
            self.handle_http(404, "text/html")

    def send_json(self, data: dict):
        self.handle_http(200, "text/json")
        self.wfile.write(bytes(json.dumps(data), "UTF-8"))

    def read_json(self) -> dict:
        content_len = int(self.headers["Content-length"])
        data_string = self.rfile.read(content_len)
        return json.loads(data_string)
