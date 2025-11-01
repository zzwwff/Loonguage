# Loonguage
## What is Loonguage?
Loonguage is a language specified to generate assembly code to run on a specified CPU.
The CPU is self-made on FPGA, using a set of instructions designed for this CPU.
This repository contains a compiler to compile Loonguage and a user-friendly interface to edit, run and debug the code in Qt.

## How is the compiler down?
Loonguage compiler has four phases.
### Lexical Analysis
Use flex to generate lexical analyzer to transform raw code into token list.
### Syntax Analysis
Use Bison to generate lexical analyzer to transform token list into abstract syntax tree.
### Semantic Analysis
On syntax tree, perform type check, object check and so on to check its validity.
### Code Generation
Generate ASM code using special instruction set designated for homemade CPU.

## What is the structure of this repository?
You can open the root path in repository in Qt Design to generate the user interface, which is used as a design environment for Loonguage writer.
The folder /Compiler contains the core of the compiler, which is a Visual Studio project.