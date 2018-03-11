#include "LR1.h"
#include <string>

void LR1::ReadLr1(std::string file_name) {
    std::cout << "READLR1" << std::endl;
}

LR1::LR1() {
    ReadLr1("SL3.lr1");
};

LR1::Lr1(std::string file_name) {
    ReadLr1(file_name);
};
