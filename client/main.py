# TODO: RAW CLIENT! NOT FOR DEMONSTRATION! ONLY FOR TESTING!

import asyncio
import socket
import random
import json

keys = [
    "tree",
    "cube",
    "pen",
    "book",
    "car",
    "dog",
    "elephant",
    "fish",
    "guitar",
    "yamaha",
]


async def tcp_echo_client(request, sock):
    print(f"[CLIENT] Sent request: {request}")
    sock.sendall(json.dumps(request).encode())
    responce = sock.recv(1024)
    print(f"[CLIENT] Received responce: {responce.decode()}")


def main():
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        host = "localhost"
        port = 8080
        sock.connect((host, port))

        for i in range(11):
            key = random.choice(keys)

            if i == 10:
                request = {"key": key, "method": "$set", "value": random.randint(1, 9)}
                asyncio.run(tcp_echo_client(request, sock))
                continue

            request = {"key": key, "method": "$get"}
            asyncio.run(tcp_echo_client(request, sock))

        sock.close()
    except ConnectionRefusedError:
        print(f"[CLIENT] Server ({host}:{port}) not available")


main()
