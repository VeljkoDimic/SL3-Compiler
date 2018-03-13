#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

namespace Utils {
    template<typename Out>
    void split(const std::string &s, char delim, Out result) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            *(result++) = item;
        }
    }

    static inline std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));
        return elems;
    }

    static inline int ReadIntLineFromFile(std::ifstream &file) {
        int num = 0;
        std::string line = "";
        try {
            getline(file, line);
            std::istringstream iss(line);
            iss >> num;
        } catch(...) {
            std::cout << "ERROR: Unable to read integer at line "
                << line << std::endl;
        }
        return num;
    }
}

#endif
