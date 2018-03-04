# Simplified Lisp-Like Language Specifications
SL3 is a simplified version of Lisp, inspired by [WLP4](https://www.student.cs.uwaterloo.ca/~cs241/wlp4/WLP4.html)

## Lexical Syntax
* WHITESPACE
    * SPACE: (ascii 32)
    * TAB: (ascii 9)
    * NEWLINE: (ascii 10)
    * COMMENT: the string ";" followed by all the characters up to and including the next NEWLINE
* NUM: a string consisting of a single digit (in the range 0-9) or two or more digits, the first of which is not 0; the numeric value of a NUM token cannot exceed 2^31-1
* ID: a string consisting of a letter (in the range a-z or A-Z) followed by zero or more letters and digits (in the range 0-9), but not equal to keywords
* LPAREN: the string "("
* RPAREN: the string ")"
* DEFINE: the string "define"
* PLUS: the string "+"
* MINUS: the string "-"
* STAR: the string "*"
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
* VAR: the string "var"
* WRITE: the string "write"
* LAMBDA: the string "lambda"

## Context-Free Syntax
* start → LPAREN sexp RPAREN
* sexps →
* sexps → sexp sexps
* sexp → NUM
* sexp → ID
* sexp → TRUE
* sexp → NIL
* sexp → cond
* sexp → LPAREN VAR ID sexp RPAREN
* cond → LPAREN sexp sexp sexp RPAREN
* sexp → LPAREN DEFINE ID sexp RPAREN
* sexp → LPAREN PLUS sexps RPAREN
* sexp → LPAREN MINUS sexps RPAREN
* sexp → LPAREN STAR sexps RPAREN
* sexp → LPAREN SLASH sexps RPAREN
* sexp → LPAREN MOD sexps RPAREN
* sexp → LPAREN EQ sexps RPAREN
* sexp → LPAREN NE sexps RPAREN
* sexp → LPAREN LT sexps RPAREN
* sexp → LPAREN GT sexps RPAREN
* sexp → LPAREN LE sexps RPAREN
* sexp → LPAREN GE sexps RPAREN
* sexp → LPAREN AND sexps RPAREN
* sexp → LPAREN OR sexps RPAREN
* sexp → LPAREN NOT sexps RPAREN
* sexp → LPAREN LOGAND sexps RPAREN
* sexp → LPAREN LOGIOR sexps RPAREN
* sexp → LPAREN LOGXOR sexps RPAREN
* sexp → LPAREN LOGNOR sexps RPAREN
* sexp → LPAREN LOGEQV sexps RPAREN
* sexp → LPAREN WRITE sexps RPAREN
* sexp → LPAREN LPAREN LAMBDA LPAREN params RPAREN LPAREN sexp RPAREN RPAREN sexps RPAREN
* params →
* params → ID params
