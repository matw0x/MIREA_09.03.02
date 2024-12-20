import curses

def emergency_action(stdscr):
    """Функция для выполнения аварийных действий."""
    stdscr.clear()
    stdscr.addstr(0, 0, "Аварийные действия: система остановлена!")
    stdscr.refresh()
    curses.napms(2000)

def keyboard_handler(stdscr):
    """Функция для запуска обработки нажатий клавиш с использованием curses."""
    curses.curs_set(0)
    stdscr.clear()
    stdscr.addstr(0, 0, "Программа работает. Нажмите F10 для аварийного завершения или ESC для выхода.")
    stdscr.refresh()

    while True:
        key = stdscr.getch()

        if key == 27:
            stdscr.clear()
            stdscr.addstr(1, 0, "Выход по ESC.")
            stdscr.refresh()
            curses.napms(2000)
            break

        if key == curses.KEY_F10:
            stdscr.clear()
            stdscr.addstr(1, 0, "Нажата горячая клавиша F10.")
            stdscr.refresh()
            emergency_action(stdscr)
            break

def main():
    """Главная функция для запуска программы с curses."""
    curses.wrapper(keyboard_handler)

if __name__ == "__main__":
    main()