#include "pbmloader.hpp"

namespace HokusBlokus::PBM {
    PBMImage PBMLoader::LoadPBM(std::string path) {
        unsigned int width = 0;
        unsigned int height = 0;

        std::ifstream inputStream(path);
        if (!inputStream) {
            std::cout << "Unable to open pbm file at: " << path << "\n";
            std::exit(1);
        }

        //Read bitmmap metadata. We will only load the P4 (binary) format
        //Step through every line until the binary data begins
        std::string line;
        int lineCount = 0;
        while (std::getline(inputStream, line) && width == 0 && height == 0) {
            if (lineCount == 0) {
                if (line != "P4") {
                    std::cout << "Unable to read pbm file. Expected type P4.\n";
                    std::exit(1);
                }
            } else if (line[0] != '#') {
                std::vector<std::string> words = SplitStringIntoWords(line, ' ');
                width = std::stoi(words[0]);
                height = std::stoi(words[1]);
            }
            lineCount++;
        }
        inputStream.close();

        //Read bitmap data
        boost::dynamic_bitset<> data = boost::dynamic_bitset<>(width * height);
        int bitCount = 0;
        for (char byte : line) {
            for (int i = 7; i >= 0; i--) {
                if ((byte >> i) & 1) {
                    data[bitCount] = 1;
                }
                bitCount++;
                if (bitCount % width == 0) {  //End of line encountered. We ignore the last bits in the line as they are padding
                    break;
                }
            }
        }
        return PBMImage(width, height, data);
    }

    std::vector<std::string> PBMLoader::SplitStringIntoWords(std::string string, char delimiter) {
        std::vector<std::string> words = std::vector<std::string>();
        while (!string.empty()) {
            unsigned int pos = string.find(delimiter);
            if (pos != std::string::npos) {
                std::string word = string.substr(0, pos);
                words.push_back(word);
                string = string.substr(pos + 1);
            } else {
                words.push_back(string);
                string.clear();
            }
        }
        return words;
    }
}  // namespace HokusBlokus::PBM