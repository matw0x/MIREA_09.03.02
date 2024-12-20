import os
import time

def child_process():
    print(f"Дочерний процесс с PID: {os.getpid()}, родительский PID: {os.getppid()}")
    time.sleep(5)
    print(f"Дочерний процесс с PID: {os.getpid()} теперь сирота, его родительский PID: {os.getppid()}")

def main():
    pid = os.fork()
    
    if pid > 0:
        print(f"Родительский процесс с PID: {os.getpid()}")
        print(f"Создан дочерний процесс с PID: {pid}")
        time.sleep(2)
        print("Родительский процесс завершает работу")
    else:
        child_process()

if __name__ == "__main__":
    main()