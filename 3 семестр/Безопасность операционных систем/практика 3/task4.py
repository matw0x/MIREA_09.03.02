import threading

def thread_function(param1, param2, param3):
    print(f"Параметр 1: {param1}")
    print(f"Параметр 2: {param2}")
    print(f"Параметр 3: {param3}")

if __name__ == "__main__":
    param1 = 666
    param2 = 3.14
    param3 = "HELLO"

    thread = threading.Thread(target=thread_function, args=(param1, param2, param3))
    thread.start()
    thread.join()

    print("Поток завершен")