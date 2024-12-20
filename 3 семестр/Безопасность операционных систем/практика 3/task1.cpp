#include <iostream>
#include <unistd.h>

int main() {
    std::cout << "PID: " << getpid() << std::endl;
    std::cout << "PPID: " << getppid() << std::endl;

    return 0;
}