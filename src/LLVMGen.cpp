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

        if (prod_string == "sexp TRUE") {
            ++instruction;
            s << '%' << instruction << " = add i32 0, 1\n";
        }

        if (prod_string == "sexp NIL") {
            ++instruction;
            s << '%' << instruction << " = add i32 0, 0\n";
        }

        if (prod_string == "sexp LPAREN COND sexp sexp sexp RPAREN") {
            s << "; CONDITIONAL START\n";

            // This will get the conditional value
            s << code(children.at(2));

            // This is the address of the condition value
            int i32_cond_reg = instruction;

            // Memory which stores result
            int mem_value = ++instruction;
            s << '%' << mem_value << " = alloca i32\n";

            // Condition value as condition
            int cond_reg = ++instruction;
            s << '%' << cond_reg << " = icmp ne i32 0, %"
                << i32_cond_reg << '\n';

            int true_label = ++instruction;
            std::string true_string = code(children.at(3));
            int false_label = ++instruction;
            std::string false_string = code(children.at(4));
            int end_label = ++instruction;

            // Branch
            s << "br i1 %" << cond_reg << ", label %"
                << true_label << ", label %" << false_label << '\n';

            // True branch
            s << "; <label>:" << true_label << ":\n";
            s << true_string;
            s << "store i32 %" << (false_label-1)
                << ", i32* %" << mem_value << '\n';
            s << "br label %" << end_label << '\n';

            // False branch
            s << "; <label>:" << false_label << ":\n";
            s << false_string;
            s << "store i32 %" << (end_label-1)
                << ", i32* %" << mem_value << '\n';
            s << "br label %" << end_label << '\n';

            // End branch
            s << "; <label>:" << end_label << ":\n";
            ++instruction;
            s << '%' << instruction << " = load i32, i32* %"
                << mem_value << '\n';

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
