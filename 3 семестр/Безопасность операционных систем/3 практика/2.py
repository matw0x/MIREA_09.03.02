import threading
import time

sem_point_2 = threading.Semaphore(0)
sem_point_3 = threading.Semaphore(0)
sem_point_4 = threading.Semaphore(0)

semaphore_var = [0]

def acquire_semaphore(sem, name):
    print(f"Поток '{name}' начался и ожидает семафор.")
    sem.acquire()
    print(f"Поток '{name}' захватывает семафор.")
    print(f"Переменная семафора равна: {semaphore_var[0]}. Поток '{name}' выходит из семафора.")

def release_semaphore(sem, name):
    semaphore_var[0] += 1
    sem.release()
    print(f"Поток '{name}' захватывает семафор.")
    print(f"Переменная семафора равна: {semaphore_var[0]}.")

def process_A():
    print("Поток 'A' начался и ожидает семафор.")
    print("Поток 'A' захватывает семафор.")
    threading.Thread(target=process_B).start()
    threading.Thread(target=process_C).start()
    threading.Thread(target=process_I).start()
    threading.Thread(target=process_J).start()

def process_B():
    time.sleep(1)
    print("Поток 'B' начался и ожидает семафор.")
    release_semaphore(sem_point_2, 'B')

def process_C():
    time.sleep(1.5)
    print("Поток 'C' начался и ожидает семафор.")
    release_semaphore(sem_point_2, 'C')

def process_I():
    time.sleep(2)
    print("Поток 'I' начался и ожидает семафор.")
    release_semaphore(sem_point_2, 'I')

def process_J():
    acquire_semaphore(sem_point_2, 'J')
    print("Поток 'J' начался и ожидает семафор.")
    release_semaphore(sem_point_3, 'J')

def process_D():
    time.sleep(1)
    print("Поток 'D' начался и ожидает семафор.")
    release_semaphore(sem_point_3, 'D')

def process_E():
    time.sleep(1.5)
    print("Поток 'E' начался и ожидает семафор.")
    release_semaphore(sem_point_3, 'E')

def process_F():
    time.sleep(2)
    print("Поток 'F' начался и ожидает семафор.")
    release_semaphore(sem_point_3, 'F')

def process_G():
    acquire_semaphore(sem_point_3, 'G')
    print("Поток 'G' начался и ожидает семафор.")
    release_semaphore(sem_point_4, 'G')

def process_H():
    acquire_semaphore(sem_point_3, 'H')
    print("Поток 'H' начался и ожидает семафор.")
    release_semaphore(sem_point_4, 'H')

def process_K():
    acquire_semaphore(sem_point_4, 'K')
    print("Поток 'K' начался.")
    print("The End.")

process_A()
