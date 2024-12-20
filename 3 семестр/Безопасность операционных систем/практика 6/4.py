import signal
import time
from datetime import datetime

x = 20
total_time = 0

def handler(signum, frame):
    global x, total_time
    current_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
    
    total_time += x
    print(f"Прошло {x} секунд! Текущее время: {current_time}")
    
    x += 20

signal.signal(signal.SIGALRM, handler)
signal.setitimer(signal.ITIMER_REAL, x, 20)

try:
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    print(f"Программа завершена")
