import threading

def thread_function(arg1, arg2, arg3):
    print(f"Поток начал выполнение с аргументами: {arg1}, {arg2}, {arg3}")
    result = arg1 + arg2 + arg3
    print(f"Результат выполнения потока: {result}")
    return result
def create_thread(args):
    thread = threading.Thread(target=thread_function, args=args)
    thread.start()
    thread.join()
if __name__ == "__main__":
    args = (5, 10, 15)
    print("Создание потока...")
    create_thread(args)
    print("Поток завершён.")