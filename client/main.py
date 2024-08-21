import asyncio
import random
import sys

from client_of import ClientOf

KEYS = [
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


async def main():
    SERVER_ADDRESS = ("localhost", 8080)

    client = ClientOf(SERVER_ADDRESS)
    while True:
        try:
            await client.connect_to_server()

            # Из ТЗ:
            # "Выбирает случайный ключ из захардкоженого списка и выполняет на сервере $get с вероятностью 99%,
            # а в 1% случаев записывает случайные данные в этот ключ, выполняя $set."
            for i in range(10000):
                key = random.choice(KEYS)

                if i % 100 == 0:
                    request = {
                        "key": key,
                        "method": "$set",
                        "value": str(random.randint(1, 9)),
                    }

                    await client.execute_request(request)
                    continue

                request = {"key": key, "method": "$get"}
                await client.execute_request(request)

            break
        except ConnectionRefusedError:
            print(f"[CLIENT] Server {SERVER_ADDRESS} not available. Retrying...\r")
            await asyncio.sleep(1)
        except ConnectionResetError:
            print(f"[CLIENT] Connection reset by server. Retrying... \r")
            client.disconnect_from_server()
        except BrokenPipeError:
            print(f"[CLIENT] Server closed socket. Retrying... \r")
            client.disconnect_from_server()


try:
    asyncio.run(main())
except KeyboardInterrupt:
    print(f"\nInterrupt by user, goodbye!")
    sys.exit()
