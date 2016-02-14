-------------------------
Introduction
-------------------------
interpreter is a programme that can build expression trees from a input 
expression in prefix-notation. Given a valid expression it can build 
the expression, save it as in dot syntax, print in infix notation, 
evaluate in x at a given value, differentiate with respect to x and 
locally simplify the expression

In the current version tester.py will generate a random valid expression in 
prefix-notation of depth <depth>, use the interpreter to convert the 
expression to infix, differentiate it using sympy, then let the 
interpreter build and differentiate the expression and output the two answers.

-------------------------
Contents
-------------------------
interpreter: the actual programme
README.txt: this file 
interpreter.cpp: source code for the interpreter
expTree.h: header of the expression tree
Tree.h: expTree dependency
tester.py: python script for testing, see Usage
Makefile: the makefile to compile the project
token.h: header declaration of Token
token.cpp: implementation of Token 
expTree.cpp: implementation of the expression tree

-------------------------
Usage
-------------------------
Commandline:
   Example:  ./interpreter < instructions

Example instruction file:
exp / * + 5 3 sin ^ x 2 pi
diff
eval -0.2244
simp
print
dot file.txt
end

syntax:
   - commands are separated by line breaks, 
      make sure no chars before the command!
   - expressions are separated by spaces
   - except for 'print', 'dot' and 'end' all commands replace the current tree!
   - file must follow the following grammar:

   -<cmd> <expression> [linebreak]:
      -<cmd>:
         -exp <expression>: builds the tree of the given expression.
                             Expression must be in prefix-notation
         -eval <value>: evaluates the expression in x at <value>
         -simp: simplifies the expression and evaluate known expressions
         -print: prints the saved expression in infix-notation to command line
         -dot <filename>: saves current expression in <filename> in dot syntax
         -diff: differentiates current expression with respect to x 
         -end: ends the program

      -<expression>: <binary> <expression> <expression> |^ <expression> <number> 
         |<unary> <expression> | <nullary>
      -<binary>: + | - | * | /
      -<unary>: sin | cos
      -<nullary>: <number> | <variable>
      -<number>: [+|-]<unsigned>[.<unsigned>] | pi
      -<unsigned>: <digit><unsigned>|<digit>
      -<digit>: 0 | 1 | ... | 9
      -<variable>: a | b | ... | z  

tester.py:

python tester.py <depth>
Example: python tester.py 5
<depth> is the depth of the expression. Current version generates random 
has the programme differentiate it and differentiates itself and outputs the 
two answers for comparison. To have it do something else e.g. evaluate, simplify
etc. one should edit the instructions string on line 94 to include the desired
commands as well as have sympy preform the relevant operations within the 
script itself. Make sure to use correct spacing! 

-------------------------
Dependencies
-------------------------

C++:
   Tree.h
      fstream
      string
   algorithm
   sstream
   iostream
   cmath

Python:
   sympy
   random
   string
   sys
   os
   subprocess 

-------------------------
Discussion
-------------------------
Simplifying:
The tree can only simplify it's direct children so it cannot join similar 
expressions somewhere else in the tree. Also things like --3 being converted to 3 aren't supported yet. 

Precision:
doubles are used, so this tree should not be used for high precision. In addition if the numbers used are very large or small or the difference between the two numbers is very large the rounding errors become very large as well

-------------------------
Authors
-------------------------

- Daniel Vente (s1207318) 
- Heleen Otten (s1235672)

-------------------------
History
-------------------------

Version: v1.0
Last update: 03-12-2015

