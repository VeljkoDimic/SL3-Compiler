#include <string>
#include <iostream>
#include "LLVMGen.h"
#include "CodeGenFailure.h"

std::string LLVMGen::code(Node* n) {
    std::stringstream s;
    Production prod = n->getProduction();
    s << prod;
    std::string prod_string = s.str();
    s.str("");
    std::vector<std::string> rhs = prod.getRhs();

    std::deque<Node*> children = n->getChildren();

    try {
        if (prod_string == "start BOF sexp EOF") {
            s << code(children.at(1));
        }

        if (prod_string == "sexps") {
            //Do nothing
        }

        if (prod_string == "sexp NUM") {
            //TODO: more efficient way than add?
            ++instruction;
            s << '%' << instruction << " = add i32 0, "
                << children.at(0)->getProduction().getRhs().at(0)
                << '\n';
        }

        if (prod_string == "sexp ID") {
            std::string var =
                children.at(0)->getProduction().getRhs().at(0);

            // If the variable is not found in the symbol table
            if (symbol_table.find(var) == symbol_table.end()) {
                throw CodeGenFailure("Variable '" + var + "' not defined");
            }

            //TODO: More effective method
            ++instruction;
            s << '%' << instruction << " = add i32 0, "
                << symbol_table.at(var) << '\n';
        }

    } catch (CodeGenFailure &f) {
        throw f;
    } catch (...) {
        throw CodeGenFailure("Failed code generation at production '"
                + prod_string + "'");
    }

    return s.str();
}

std::string LLVMGen::printNumCode(int i) {
    std::string num = std::to_string(i);
    std::stringstream s;
    for (char& c : num) {
        ++instruction;
        s << '%' << instruction
            << " = tail call i32 @putchar(i32 " <<
            (int)c << ")\n";
    }
    ++instruction;
    s << '%' << instruction
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
