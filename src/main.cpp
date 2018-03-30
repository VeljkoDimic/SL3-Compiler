#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iterator>
#include <fstream>
#include <ctime>
#include "Utils.h"
#include "LR1.h"
#include "DFA.h"
#include "Node.h"
#include "LLVMGen.h"
#include "ScanningFailure.h"
#include "ParsingFailure.h"
#include "CodeGenFailure.h"

struct Flags {
    // All files to be inputted
    std::vector<std::string> input_files;

    // Verbose option for debugging
    bool verbose = false;

    // Help message
    bool help = false;

    // Output file names
    std::string llvm_output_file = "";
    std::string binary_output_file = "";

    // Compiler optimization. 1, 2, or 3
    int optimization = 0;

    // True if there is an error with the flags
    bool error = false;
};

Flags getFlags(int argc, char ** argv);

int main(int argc, char** argv) {
    Flags flags = getFlags(argc, argv);

    if (flags.error) {
        std::cout << "See 'sl3 -help' for help" << std::endl;
        return 0;
    }

    if (flags.help) {
        std::cout << "SL3: Simple Lisp-Like Language" << std::endl;
        std::cout << "Usage: sl3 [options] [source files] [options]" <<std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "-h, -help\t\t\tDisplay the current help information"
            << std::endl;
        std::cout << "-v, -verbose\t\t\tDisplay verbose debugging info"
            << std::endl;
        std::cout << "-llvm, -emit-llvm [file]\t"
            << "Choose name of intermediate llvm file. If" << std::endl;
        std::cout << "\t\t\t\tempty, no intermediate file generated"
            << std::endl;
        std::cout << "-b, -bin [file]\t\t\t"
            << "Choose name of outputted binary file. If empty," << std::endl;
        std::cout << "\t\t\t\tdefault binary generated"
            << std::endl;
        std::cout << "-O, -O2, -O3\t\t\tLevel of optimization. "
            << "None for no optimization" << std::endl;

        return 0;
    }

    // Keeps track of the number of binaries created for each input
    int num_bin_generated = 0;

    // Generate outputs for all files
    for (auto file_name : flags.input_files) {

        // Lexing
        if (flags.verbose) {
            std::cout << "Lexing..." << std::endl;
        }

        std::vector<Token> tokens;

        try {
            std::ifstream input_file(file_name);

            DFA dfa;
            std::string line;

            while (getline(input_file, line)) {
                std::vector<Token> scanned_tokens = dfa.scan(line);
                tokens.insert(std::end(tokens),
                        std::begin(scanned_tokens),
                        std::end(scanned_tokens));
            }

            input_file.close();
        } catch (ScanningFailure &f) {
            std::cerr << f.getMessage() << std::endl;
            return 1;
        }
        catch (...) {
            std::cerr << "Unable to open file " << file_name << std::endl;
        }

        if (flags.verbose) {
            for (int i = 0; i < tokens.size(); ++i) {
                std::cout << tokens.at(i) << std::endl;
            }
        }

        // Parsing
        if (flags.verbose) {
            std::cout << std::endl << "Parsing..." << std::endl;
        }
        Node* root;
        try {
            LR1 lr1("SL3.lr1");
            root = lr1.Parse(tokens);

            if (flags.verbose) {
                std::cout << *root << std::endl;
            }
        } catch (ParsingFailure &f) {
            std::cerr << f.getMessage() << std::endl;
            return 1;
        }

        // Code Generation (LLVM)
        if (flags.verbose) {
            std::cout << std::endl << "Generating Code..." << std::endl;
        }
        try {
            std::string time = std::to_string(std::time(0));
            std::string llvm_file_prefix = "llvm_" + time;
            std::string llvm_file_name = llvm_file_prefix + ".ll";

            if (flags.llvm_output_file != "") {
                llvm_file_name = flags.llvm_output_file;
                llvm_file_prefix = llvm_file_name;

                // 'test' => 'test.o'
                // 'test.ll' => 'test.o'
                // 'test.txt' => 'test.txt.o'
                // 'test.txt.ll' => 'test.txt.o'
                size_t dot = llvm_file_name.find_last_of('.');
                if (dot != std::string::npos) {
                    std::string file_type = llvm_file_name.substr(dot+1);
                    if (file_type == "ll") {
                        llvm_file_prefix = llvm_file_name.substr(0,dot);
                        if (num_bin_generated) {
                            llvm_file_prefix +=
                                std::to_string(num_bin_generated+1);
                        }
                        llvm_file_name = llvm_file_prefix + ".ll";
                    }
                    else if (num_bin_generated) {
                        llvm_file_name += std::to_string(num_bin_generated+1);
                        llvm_file_prefix += std::to_string(num_bin_generated+1);
                    }
                }
                else if (num_bin_generated) {
                    llvm_file_name += std::to_string(num_bin_generated+1);
                    llvm_file_prefix += std::to_string(num_bin_generated+1);
                }
            }

            LLVMGen llvm(root);
            try {
                // Create .ll file
                std::ofstream llvm_file;
                llvm_file.open(llvm_file_name);
                llvm_file << llvm.getLlvm();
                llvm_file.close();
            } catch (...) {
                std::cerr << "Failed to open llvm output file"
                    << std::endl;
            }

            // Optimization in LLVM
            if (flags.optimization) {
                std::string opt_command = "opt -S -O";
                opt_command += std::to_string(flags.optimization);
                opt_command += " " + llvm_file_name + " -o " + llvm_file_name;
                system(opt_command.c_str());
            }

            // Create .o file
            std::string llc_command = "llc -filetype=obj " + llvm_file_name;
            system(llc_command.c_str());

            // Create binary
            // Defaults are a.out, b.out, ...
            // Specified are 'output', 'output2', ...
            std::stringstream output_bin_name;
            if (flags.binary_output_file == "") {
                char default_output_letter = 'a' + num_bin_generated;
                output_bin_name << default_output_letter << ".out";
            }
            else {
                output_bin_name << flags.binary_output_file;
                if (num_bin_generated) {
                    output_bin_name << (num_bin_generated+1);
                }
            }
            std::string gcc_command = "gcc " + llvm_file_prefix + ".o"
                + " -o " + output_bin_name.str();
            system(gcc_command.c_str());

            // Remove llvm object file
            std::string rm_o = "rm " + llvm_file_prefix + ".o";
            system(rm_o.c_str());

            // Remove llvm file only if no llvm output specified
            if (flags.llvm_output_file == "") {
                std::string rm_ll = "rm " + llvm_file_name;
                system(rm_ll.c_str());
            }

            if (flags.verbose) {
                std::cout << "Code generated" << std::endl;
            }

            ++num_bin_generated;
        } catch (CodeGenFailure &f) {
            std::cerr << f.getMessage() << std::endl;
            return 1;
        }
    }

    return 0;
}

Flags getFlags(int argc, char ** argv) {
    Flags flags;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg.size() > 1 && arg[0] == '-') {
            std::string flag=arg.substr(1, std::string::npos);

            if (flag == "v" || flag == "verbose") {
                flags.verbose = true;
            }
            else if (flag == "h" || flag == "help") {
                flags.help = true;
            }
            else if (flag == "llvm" || flag == "emit-llvm") {
                if (i + 1 > argc) {
                    std::cout
                        << "LLVM output file name must succeed the '-llvm' flag"
                        << std::endl;
                    flags.error = true;
                }
                flags.llvm_output_file = argv[++i];
            }
            else if (flag == "b" || flag == "bin") {
                if (i + 1 > argc) {
                    std::cout
                        << "Binary output file name must succeed the '-bin' flag"
                        << std::endl;
                    flags.error = true;
                }
                flags.binary_output_file = argv[++i];
            }
            else if (flag == "O" || flag == "O1") {
                flags.optimization = 1;
            }
            else if (flag == "O2") {
                flags.optimization = 2;
            }
            else if (flag == "O3") {
                flags.optimization = 3;
            }
            else {
                std::cout << "Unexpected flag '" << flag
                    << "'" << std::endl;
                flags.error = true;
            }
        }
        else {
            flags.input_files.push_back(arg);
        }
    }

    if (flags.input_files.size() < 1 && !flags.help) {
        std::cout << "You must specify input files to run SL3" << std::endl;
        flags.error = true;
    }
    
    return flags;
}
