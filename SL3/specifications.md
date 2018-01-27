# Simplified Lisp-Like Language Specifications
SL3 is a simplified version of Lisp, inspired by [WLP4](https://www.student.cs.uwaterloo.ca/~cs241/wlp4/WLP4.html)

## Lexical Syntax
* WHITESPACE
    * SPACE: (ascii 32)
    * TAB: (ascii 9)
    * NEWLINE: (ascii 10)
    * COMMENT: the string ";" followed by all the characters up to and including the next NEWLINE
* NUM: a string consisting of a single digit (in the range 0-9) or two or more digits, the first of which is not 0; the numeric value of a NUM token cannot exceed 2^31-1
* LPAREN: the string "("
* RPAREN: the string ")"
* DEFINE: the string "define"
* PLUS: the string "+"
* MINUS: the string "-"
* STAR: the string "TODO: STAR"
* SLASH: the string "/"
* MOD: the string "mod"
* EQ: the string "="
* NE: the string "/="
* LT: the string "<"
* GT: the string ">"
* LE: the string "<="
* GE: the string ">="
* AND: the string "and"
* OR: the string "or"
* NOT: the string "not"
* LOGAND: the string "logand"
* LOGIOR: the string "logior"
* LOGXOR: the string "logxor"
* LOGNOR: the string "lognor"
* LOGEQV: the string "logeqv"
* TRUE: the string "t"
* NIL: the string "nil"
* COND: the string "cond"
* IF: the string "if"
* WHEN: the string "when"
* CASE: the string "case"
* LOOP: the string "loop"
* FOR: the string "for"
* DO: the string "do"
* SETQ: the string "setq"
* DEFVAR: the string "defvar"
* LET: the string "let"
* PROG: the string "prog"
* DEFMACRO: the string "defmacro"
* DEFUN: the string "defun"
* WRITE: the string "write"
* LAMBDA: the string "lambda"
