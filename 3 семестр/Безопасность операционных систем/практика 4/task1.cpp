#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <cstdlib>
#include <ctime>

const int NUM_PHYSICAL_FRAMES = 10;
const int PAGE_SIZE = 4;

class Disk {
public:
    void swapIn(int pageID) {
        // Simulate loading a page from disk
        std::cout << "Swapping in page " << pageID << " from disk.\n";
    }

    void swapOut(int pageID) {
        // Simulate saving a page to disk
        std::cout << "Swapping out page " << pageID << " to disk.\n";
    }
};

class PageTable {
public:
    std::unordered_map<int, int> table; // Maps virtual page numbers to physical frames or -1 for disk
    Disk* disk;

    PageTable(Disk* d) : disk(d) {}

    int getFrame(int pageID) {
        if (table.find(pageID) == table.end()) {
            disk->swapIn(pageID);
            return -1; // page not in memory
        }
        return table[pageID];
    }

    void setFrame(int pageID, int frame) {
        table[pageID] = frame;
    }
};

class PhysicalMemory {
public:
    std::vector<int> frames;

    PhysicalMemory() {
        frames.resize(NUM_PHYSICAL_FRAMES, -1); // Initialize empty frames
    }

    int allocateFrame(int pageID) {
        for (int i = 0; i < NUM_PHYSICAL_FRAMES; ++i) {
            if (frames[i] == -1) {
                frames[i] = pageID;
                return i;
            }
        }
        return -1; // Memory full
    }

    void freeFrame(int frameID) {
        frames[frameID] = -1;
    }
};

class Process {
public:
    int pid;
    PageTable pageTable;

    Process(int id, Disk* disk) : pid(id), pageTable(disk) {}
};

class MemoryManager {
public:
    Disk disk;
    PhysicalMemory memory;
    std::vector<Process> processes;

    MemoryManager(int numProcesses) {
        for (int i = 0; i < numProcesses; ++i) {
            processes.emplace_back(i, &disk);
        }
    }

    void accessPage(int processID, int pageID) {
        Process& process = processes[processID];
        int frame = process.pageTable.getFrame(pageID);
        if (frame == -1) {
            frame = memory.allocateFrame(pageID);
            if (frame != -1) {
                process.pageTable.setFrame(pageID, frame);
                std::cout << "Allocated frame " << frame << " to page " << pageID << " of process " << processID << "\n";
            } else {
                std::cout << "Memory full, swap needed.\n";
            }
        } else {
            std::cout << "Page " << pageID << " of process " << processID << " is in frame " << frame << "\n";
        }
    }

    void simulate() {
        srand(time(0));
        for (int i = 0; i < 10; ++i) {
            int processID = rand() % processes.size();
            int pageID = rand() % 10;
            std::cout << "Accessing page " << pageID << " for process " << processID << "\n";
            accessPage(processID, pageID);
        }
    }
};

int main() {
    MemoryManager manager(2); // Simulate 2 processes
    manager.simulate();
    return 0;
}
