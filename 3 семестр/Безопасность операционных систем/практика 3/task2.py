import threading
import time
 
_semaphore1 = None
_padding = 0
_semaphoreI = 0
stop_threads = False
 
 
def worker(name, semaphore):
    global _padding, _semaphoreI, stop_threads
    print(f"Поток {name} начался и ожидает семафор.\n")
    semaphore.acquire()
    padding = _padding + 100
    _padding = padding
    print(f"Поток {name} захватывает семафор.\n")
    time.sleep(1 + padding / 1000)
    print(f"Поток {name} в семафоре.\n")
    print(f"Переменная семафора равна: {_semaphoreI}. Поток {name} выходит из семафора\n")
    _semaphoreI += 1
 
 
 
def main():
    global _semaphoreI, stop_threads
 
    semaphoreA = threading.Semaphore(0)
    semaphoreBC = threading.Semaphore(0)
    semaphoreI = threading.Semaphore(0)
    semaphoreJ = threading.Semaphore(0)
    semaphoreDEF = threading.Semaphore(0)
    semaphoreGH = threading.Semaphore(0)
 
    a = threading.Thread(target=worker, args=("'A'", semaphoreA))
    a.start()
    time.sleep(0.5)
    semaphoreA.release()
    time.sleep(3)
    a.join()
 
    print()
    _semaphoreI = 0
 
    b = threading.Thread(target=worker, args=("'B'", semaphoreBC))
    c = threading.Thread(target=worker, args=("'C'", semaphoreBC))
    i = threading.Thread(target=worker, args=("'I'", semaphoreI))
    j = threading.Thread(target=worker, args=("'J'", semaphoreJ))
 
    b.start()
    c.start()
    j.start()
    i.start()
 
 
    time.sleep(0.5)
    semaphoreBC.release(2)
    semaphoreJ.release(1)
    time.sleep(3)
    b.join()
    c.join()
 
    print()
    _semaphoreI = 0
 
    d = threading.Thread(target=worker, args=("'D'", semaphoreDEF))
    e = threading.Thread(target=worker, args=("'E'", semaphoreDEF))
    f = threading.Thread(target=worker, args=("'F'", semaphoreDEF))
    d.start()
    e.start()
    f.start()
 
    time.sleep(0.5)
    semaphoreDEF.release(3)
    time.sleep(3)
    d.join()
    e.join()
    f.join()
    j.join()
 
 
    print()
    _semaphoreI = 0
 
    g = threading.Thread(target=worker, args=("'G'", semaphoreGH))
    h = threading.Thread(target=worker, args=("'H'", semaphoreGH))
 
    g.start()
    h.start()
 
    time.sleep(0.5)
    semaphoreGH.release(2)
    semaphoreI.release(1)
    time.sleep(3)
    g.join()
    h.join()
    i.join()
 
    print()
    _semaphoreI = 0
    print("Поток 'K' начался.")
    print("\nКонец")
 
 
if __name__ == "__main__":
    main()