#include <string>
#include "LLVMGen.h"

std::string LLVMGen::code(Node* n) {
    std::stringstream s;
    Production prod = n->getProduction();
    s << prod;
    std::string prod_string = s.str();
    s.str("");
    std::vector<std::string> rhs = prod.getRhs();

    if (prod_string == "start BOF sexp EOF") {
    }

    return s.str();
}

std::string LLVMGen::printNumCode(int i) {
    std::string num = std::to_string(i);
    std::stringstream s;
    for (char& c : num) {
        ++instruction;
        s << "%" << instruction
            << " = tail call i32 @putchar(i32 " <<
            (int)c << ")\n";
    }
    ++instruction;
    s << "%" << instruction
        << "= tail call i32 @putchar(i32 " <<
        (int)'\n' << ")\n";
    return s.str();
}

std::string LLVMGen::header() const {
    std::stringstream s;
    s << "define i32 @main() local_unnamed_addr #0 {\n";
    return s.str();
}

std::string LLVMGen::footer() const {
    std::stringstream s;
    std::stringstream instructionString;
    if (instruction) {
        instructionString << '%';
    }
    instructionString << instruction;
    s << "ret i32 " << instructionString.str() << "\n"
      << "}\n" << '\n'
      << "; Function Attrs: nounwind\n"
      << "declare i32 @putchar(i32) local_unnamed_addr #1\n";
    return s.str();
}

LLVMGen::LLVMGen(Node* n) {
    instruction = 0;
    llvm << header();
    llvm << code(n);
    llvm << footer();
}

std::string LLVMGen::getLlvm() const {
    return llvm.str();
}
