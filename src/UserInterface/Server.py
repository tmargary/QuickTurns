print("PYTHON running...")

import sys
import os
from http.server import SimpleHTTPRequestHandler, HTTPServer

if len(sys.argv) != 3:
    print("Usage: python start_http_server.py <port> <path>")
    sys.exit(1)

port = int(sys.argv[1])
path = sys.argv[2]

try:
    os.chdir(path)
except Exception as e:
    print("Error changing directory:", e)
    sys.exit(1)

class CORSRequestHandler(SimpleHTTPRequestHandler):
    def end_headers(self):
        self.send_header("Access-Control-Allow-Origin", "*")
        self.send_header("Access-Control-Allow-Methods", "GET")
        self.send_header("Access-Control-Allow-Headers", "Content-Type")
        super().end_headers()

try:
    httpd = HTTPServer(("", port), CORSRequestHandler)
except Exception as e:
    print("Port 8000 already open.")

print(f"Serving on port {port} in directory {path}")

try:
    httpd.serve_forever()
except Exception as e:
    print("Error starting the HTTP server:", e)
    sys.exit(1)