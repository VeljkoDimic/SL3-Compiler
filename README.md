# Simplified Lisp-Like Language Compiler
Simplified Lisp-Like Language (SL3) is, as its name suggests, a language that is a simplification of lisp, created for learning purposes. More details on the specifications of the language can be found in SL3/specifications.md.

The compiler consists of a lexer, an SLR parser, and LLVM code generation. The compiler reads input at the lexing stage, parses into a parse tree, and then transpiles to LLVM and compiles LLVM.

To use SL3, please first download [LLVM](https://llvm.org/docs/GettingStarted.html) (I suggest using [homebrew](https://embeddedartistry.com/blog/2017/2/20/installing-clangllvm-on-osx) on OSX). Make sure the llvm executables are in your $PATH.

For some example programs, take a look at test/.

To compile:
```
$ cd build/
$ cmake ..
$ make
$ mv sl3 /usr/local/bin/
```
Note that the last step is optional, but it is suggested that you put sl3 in your bin if you will be using it frequently.

To view the output of an SL3 program,  simply execute `echo $?` after running the compiled binary. For example:
```
$ path/to/sl3 example_no_write.sl3
$ ./a.out
$ echo $?
13
```
