#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class FileManager {
private:
    const std::string filename;
    std::ifstream file;
    std::vector<std::string> dataFromFile;

    void validate() {
        file.open(filename);

        if (!file.is_open()) {
            std::cout << "Error with open the file!\n";
            return;
        }
    }

    std::vector<std::string> getDataFromFile() {
        validate();

        std::string words;
        while (!file.eof()) {
            std::string word;
            std::getline(file, word);

            words += word;
        }

        return split(words, ' ');
    }

    std::vector<std::string> split(const std::string& str, const char& delimiter) {
        std::vector<std::string> data;
        std::string s;
        if (!str.empty()) {
            for (size_t i = 0; i != str.size(); ++i) {
                if (str[i] == delimiter) {
                    if (i == 0) {
                        data.push_back("");
                    } if (s != "") {
                        data.push_back(s);
                        s = "";
                    } if (str[i + 1] == delimiter) {
                        data.push_back("");
                    } if (i == str.size() - 1) {
                        data.push_back("");
                    }
                } else {
                    s += str[i];
                    if (i == str.size() - 1) {
                        data.push_back(s);
                    }
                }
            }
        }

        return data;
    }

    void reverseWord(std::string& word) const {
        const size_t wordSize = word.size();
        for (size_t i = 0, j = 1; i != wordSize / 2; ++i, ++j) {
            std::swap(word[i], word[wordSize - j]);
        }
    }

public:
    FileManager(const std::string& filename) :
        filename(filename), dataFromFile(getDataFromFile()) {}

    void printDataFromFile() {
        validate();

        for (const std::string& word : dataFromFile) {
            std::cout << word + ' ';
        }
    }

    void reverseDataFromFile() {
        for (std::string& word : dataFromFile) {
            reverseWord(word);
        }

        const size_t dataSize = dataFromFile.size();
        for (size_t i = 0, j = 1; i != dataSize / 2; ++i, ++j) {
            std::swap(dataFromFile[i], dataFromFile[dataSize - j]);
        }

        std::ofstream f;
        f.open(filename, std::ios::app);
        f << '\n';

        for (const auto& word : dataFromFile) {
            f << word + ' ';
        }

        closeFile();
    }

    void closeFile() {
        file.close();
    }
};

int main() {
    const std::string filename = "input2.txt";

    FileManager manager(filename);
    manager.printDataFromFile();
    std::cout << "\n\n";

    manager.reverseDataFromFile();
    manager.printDataFromFile();

    manager.closeFile();

    return 0;
}