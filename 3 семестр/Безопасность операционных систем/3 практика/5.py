import threading
import time

mutex = threading.Semaphore(1)
roomEmpty = threading.Semaphore(1)
readers_count = 0

shared_data = "Изначальные данные"

def writer(writer_id):
    global shared_data
    while True:
        roomEmpty.acquire()
        print(f"Писатель {writer_id} начал писать...")
        shared_data = f"Новые данные от писателя {writer_id}"
        time.sleep(2)
        print(f"Писатель {writer_id} закончил писать.")
        roomEmpty.release()
        time.sleep(2)
def reader(reader_id):
    global readers_count
    while True:
        mutex.acquire()
        readers_count += 1
        if readers_count == 1:
            roomEmpty.acquire()
        mutex.release()
        print(f"Читатель {reader_id} читает: {shared_data}")
        time.sleep(1)

        mutex.acquire()
        readers_count -= 1
        if readers_count == 0:
            roomEmpty.release()
        mutex.release()
        time.sleep(1)
if __name__ == "__main__":
    writers = [threading.Thread(target=writer, args=(i,)) for i in range(2)]
    readers = [threading.Thread(target=reader, args=(i,)) for i in range(5)]
    for w in writers:
        w.start()
    for r in readers:
        r.start()
    for w in writers:
        w.join()
    for r in readers:
        r.join()
