all:
	g++ -Wall -Wextra -Werror -O3 main.cpp
	./a.out

valgrind:
	g++ -Wall -Wextra -Werror -O3 main.cpp
	valgrind --leak-check=full ./a.out