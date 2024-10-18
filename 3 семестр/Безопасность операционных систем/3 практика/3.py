import threading
import time
import os
def child_thread():
    print(f"Поток-сирота: Начало выполнения. PID: {os.getpid()} ")
    time.sleep(5)
    print(f"Поток-сирота: Завершение работы. PID: {os.getpid()} ")


if __name__ == "__main__":
    orphan_thread = threading.Thread(target=child_thread)
    orphan_thread.start()
    print(f"Родительский процесс: Завершение до завершения потока-сироты. PID: {os.getpid()}")
    time.sleep(2)
    print("Родительский процесс завершён.")
