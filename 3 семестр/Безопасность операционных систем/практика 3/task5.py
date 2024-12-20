import threading
import time

readers = 0
mutex = threading.Semaphore(1)
room_empty = threading.Semaphore(1)
shared_data = 0

def reader(reader_id):
    global readers
    while True:
        mutex.acquire()
        readers += 1
        if readers == 1:
            room_empty.acquire()
        mutex.release()

        print(f"Читатель {reader_id} читает данные: {shared_data}")
        time.sleep(1)

        mutex.acquire()
        readers -= 1
        if readers == 0:
            room_empty.release()
        mutex.release()

        time.sleep(2)

def writer(writer_id):
    global shared_data
    while True:
        room_empty.acquire()
        shared_data += 1
        print(f"Писатель {writer_id} изменил данные на: {shared_data}")
        time.sleep(2)
        room_empty.release()

        time.sleep(3)

def main():
    for i in range(3):
        threading.Thread(target=reader, args=(i,)).start()

    threading.Thread(target=writer, args=(1,)).start()

if __name__ == "__main__":
    main()


    