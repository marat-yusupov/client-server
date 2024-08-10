# TODO: RAW CLIENT! NOT FOR DEMONSTRATION! ONLY FOR TESTING!

import asyncio


async def tcp_echo_client(message):
    reader, writer = await asyncio.open_connection("127.0.0.1", 8080)

    print(f"Send: {message}")
    writer.write(message.encode())

    data = await reader.read(100)
    print(f"Received: {data.decode()}")

    print("Closing the connection")
    writer.close()
    await writer.wait_closed()


asyncio.run(tcp_echo_client("$get tree"))
