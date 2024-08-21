import json
import socket


class ClientOf:

    def __init__(self, server_address: tuple):
        self.server_address = server_address

    def __del__(self):
        self.disconnect_from_server()

    async def connect_to_server(self):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.connect(self.server_address)
        print(f"Connection to {self.server_address} established")

    def disconnect_from_server(self):
        self.socket.close()
        print(f"Connection to {self.server_address} closed")

    async def execute_request(self, request: str):
        print(f"[CLIENT] Sent request: {request}")
        self.socket.sendall(json.dumps(request).encode())
        responce = self.socket.recv(1024)
        print(f"[CLIENT] Received responce: {responce.decode()}")
        return responce
