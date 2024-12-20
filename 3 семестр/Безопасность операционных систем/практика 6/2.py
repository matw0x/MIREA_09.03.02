import time
import queue
import threading

class KeyboardBuffer:
    def __init__(self, frequency):
        self.buffer = queue.Queue()
        self.frequency = frequency
        self.stop_event = threading.Event()

    def add_signal(self, signal):
        """Метод для добавления сигнала в буфер."""
        self.buffer.put(signal)

    def transmit_signals(self):
        """Метод для передачи сигналов с заданной частотой."""
        while not self.stop_event.is_set():
            if not self.buffer.empty():
                signal = self.buffer.get()
                print(f"Передан сигнал: {signal}")
            time.sleep(1 / self.frequency)

    def stop_transmitting(self):
        """Метод для остановки передачи сигналов."""
        self.stop_event.set()

def simulate_keyboard_input(keyboard_buffer):
    keys = ['a', 'b', 'c', 'd', 'e']
    for key in keys:
        keyboard_buffer.add_signal(key)
        time.sleep(2)

if __name__ == "__main__":
    frequency = 2
    keyboard_buffer = KeyboardBuffer(frequency)

    transmission_thread = threading.Thread(target=keyboard_buffer.transmit_signals)
    transmission_thread.start()

    simulate_keyboard_input(keyboard_buffer)
    time.sleep(3)

    keyboard_buffer.stop_transmitting()
    transmission_thread.join()
    print("Передача завершена.")
