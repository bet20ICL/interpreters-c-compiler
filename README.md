# C-MIPS Compiler
Coursework for Compilers Module Imperial College EIE. A C90 to MIPS compiler.

Frontend: uses Flex as the lexer, Yacc as the parser - generates an AST in C++. Backend generates MIPS assembly code from the AST.


## Team Interpreters!

Nikhil Narayanan

Bryan Tan

# Requirements:
  1) QEMU MIPS Emulator: install using  ````sudo apt install qemu-user````
  2) MIPS Reference Compiler: install using ````sudo apt install qemu-user````
  3) Bison: install using ````sudo apt install bison````
  4) Flex: install using  ````sudo apt install flex````
  5) MIPS Linux GNU: install using  ````sudo apt install gcc-mips-linux-gnu````

# Usage:
  The compiler can be built by running the following command in the top-level directory:

    make bin/c_compiler

  The compilation function is invoked using the flag `-S`, with the source file and output file specified on the command line:

    bin/c_compiler -S [source-file.c] -o [dest-file.s]

# compiler_tests:

Contains a large number of example inputs, divided into various categories. The following scripts can be run to test the compiler on the testcases:

  1) Run one testcase: ````./test_compiler <name-of-testcase>````
  2) Run all testcases: ````./test_compiler````