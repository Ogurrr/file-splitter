#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

void mergeFiles(const std::vector<std::string>& filePaths, const std::string& outputFilePath) {
    std::ofstream outputFile(outputFilePath, std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Failed to create output file: " << outputFilePath << std::endl;
        return;
    }

    for (const auto& filePath : filePaths) {
        std::ifstream inputFile(filePath, std::ios::binary);
        if (!inputFile.is_open()) {
            std::cerr << "Failed to open input file: " << filePath << std::endl;
            continue;
        }

        outputFile << inputFile.rdbuf();
        if (!inputFile) {
            std::cerr << "Failed to read from input file: " << filePath << std::endl;
        }

        inputFile.close();
    }

    outputFile.close();
    std::cout << "Files have been merged into " << outputFilePath << std::endl;
}

std::vector<std::string> findSplitFiles(const std::string& baseFileName) {
    std::vector<std::string> filePaths;

    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (entry.is_regular_file() && entry.path().filename().string().find(baseFileName + ".00") == 0) {
            filePaths.push_back(entry.path().string());
        }
    }

    std::sort(filePaths.begin(), filePaths.end(), [](const std::string& a, const std::string& b) {
        // Ekstrakcja numeru z nazwy pliku i porównanie ich
        size_t indexA = std::stoi(a.substr(a.find_last_of('.') + 1));
        size_t indexB = std::stoi(b.substr(b.find_last_of('.') + 1));
        return indexA < indexB;
    });

    return filePaths;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <base_file_name>\n";
        return 1;
    }

    std::string baseFileName = argv[1];
    std::string outputFilePath = baseFileName;

    std::vector<std::string> inputFilePaths = findSplitFiles(baseFileName);
    if (inputFilePaths.empty()) {
        std::cerr << "No split files found for base file name: " << baseFileName << std::endl;
        return 1;
    }

    mergeFiles(inputFilePaths, outputFilePath);

    return 0;
}
