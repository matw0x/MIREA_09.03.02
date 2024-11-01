#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

        return split(words, ';');
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

public:
    FileManager(const std::string& filename) :
        filename(filename), dataFromFile(getDataFromFile()) {}

    void deleteEvenNumbers() {
        std::ofstream f;
        f.open(filename);

        for (auto const& element : dataFromFile) {
            switch (element[element.size() - 1]) {
            case '1':
            case '3':
            case '5':
            case '7':
            case '9':
                f << element << ';';
                break;
            default:
                break;
            }
        }

        f.close();
    }

    void printDataFromFile() {
        validate();

        for (const std::string& word : dataFromFile) {
            std::cout << word + ' ';
        }
    }

    void closeFile() {
        file.close();
    }
};

int main() {
    const std::string filename = "input1.txt";

    FileManager manager(filename);
    manager.deleteEvenNumbers();

    manager.closeFile();

    return 0;
}