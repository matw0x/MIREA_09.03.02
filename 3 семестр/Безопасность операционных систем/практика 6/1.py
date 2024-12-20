def main():
    print("Введите что-нибудь, чтобы прервать выполнение.")
    while True:
        if input():
            print("клавиша была нажата! Программа завершает работу.")
            break
if __name__ == "__main__":
    main()