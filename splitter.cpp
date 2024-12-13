#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void splitFile(const std::string& filePath, std::size_t chunkSize) {
    std::ifstream inputFile(filePath, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file: " << filePath << std::endl;
        return;
    }

    inputFile.seekg(0, std::ios::end);
    std::size_t fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    char* buffer = new char[chunkSize];
    std::size_t chunkCount = 0;

    while (fileSize > 0) {
        std::size_t currentChunkSize = std::min(chunkSize, fileSize);
        inputFile.read(buffer, currentChunkSize);

        if (!inputFile) {
            std::cerr << "Failed to read chunk from input file\n";
            delete[] buffer;
            return;
        }

        std::string outputFileName = filePath + ".00" + std::to_string(chunkCount);
        std::ofstream outputFile(outputFileName, std::ios::binary);

        if (!outputFile.is_open()) {
            std::cerr << "Failed to create output file: " << outputFileName << std::endl;
            delete[] buffer;
            return;
        }

        outputFile.write(buffer, currentChunkSize);
        if (!outputFile) {
            std::cerr << "Failed to write to output file: " << outputFileName << std::endl;
            delete[] buffer;
            return;
        }

        outputFile.close();
        fileSize -= currentChunkSize;
        ++chunkCount;
    }

    delete[] buffer;
    inputFile.close();

    std::cout << "File has been split into " << chunkCount << " parts." << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <file> <size>\n";
        return 1;
    }

    std::string filePath = argv[1];
    std::size_t chunkSize;

    try {
        chunkSize = std::stoul(argv[2]);
    } catch (const std::exception& e) {
        std::cerr << "Invalid size argument: " << argv[2] << "\n";
        return 1;
    }

    if (chunkSize == 0) {
        std::cerr << "Size must be greater than 0.\n";
        return 1;
    }

    splitFile(filePath, chunkSize);

    return 0;
}
