# Two‑Pass Assembler Project
A two‑pass assembler for a custom 12‑bit assembly language (C, Linux)

A complete assembler implementation including:
• Macro processor
• Two‑pass assembly (symbol table + code generation)
• Instruction encoding for a fictional CPU
• Error detection & reporting

Built in ANSI C as part of the Systems Programming Laboratory (20465) course at the "Open University of Israel".

# Full Documentation
## 📘 Overview
This project implements a full two‑pass assembler for a custom assembly language designed for a fictional 12‑bit CPU.
The assembler translates symbolic assembly code into machine code, including macro expansion, syntax validation, symbol resolution, and instruction encoding.

The project was developed in C under Linux, following strict compilation rules (`-ansi -Wall -pedantic`).

## 🧩 Architecture & Features
### 1. Pre‑Assembler (Macro Processor)
* Expands user‑defined macros (`mcro ... endmcro`)
* Supports multiple macro calls
* Prevents nested macro definitions
* Produces an expanded `.am` file

### 2. Two‑Pass Assembly Process
#### Pass 1 – Symbol Table Construction
* Parses all lines
* Identifies labels, directives, and instructions
* Builds the symbol table (labels, data, extern, entry)
* Calculates memory addresses for code and data

#### Pass 2 – Code Generation
* Encodes instructions into 12‑bit machine words
* Resolves symbol addresses
* Handles addressing modes (immediate, direct, register)
* Generates relocation bits (A/R/E)
* Reports syntax and semantic errors

## 🧠 CPU Model (Simplified)
* Word size: 12 bits
* Memory: 1024 words
* Registers: r0–r7
* Addressing modes: immediate (1), direct (3), register (5)
* Instruction size: 1–3 words

## 📁 Project Structure
```
assembler/
│── makefile                 # Build file
│
│── main.c
│── main.h
│
│── preAssembler.c
│── preAssembler.h
│
│── firstPass.c
│── firstPass.h
│
│── secondPass.c
│── secondPass.h
│
│── macro.c
│── macro.h
│
│── label.c
│── label.h
│
│── fileData.c
│── fileData.h
│
│── ICimage.c
│── ICimage.h
│
│── DCimage.c
│── DCimage.h
│
│── writeFiles.c
│── writeFiles.h
│
│── errors.c
│── errors.h
│
│── general.c
│── general.h
│
│── utils.c
│── utils.h
│
│── files/
│     ├── file1.as
│     ├── file2.as
│     ├── file3.as
│     ├── file1_screenshot.png
│     ├── file2_screenshot.png
│     ├── file3_screenshot.png
│     # Example input files + screenshots of assembler output
```


## 📤 Output Files
Given an input file file.as, the assembler may generate:
| File | Description |
| --- | --- |
| ``file.ob`` | Encoded machine code (base‑32 format) |
| ``file.ent`` | Entry symbols |
| ``file.ext`` | External symbol references |
| ``file.am`` | Expanded source after macro processing |

## 🧪 Example
### Input (`example.as`)
mcro m1
    inc r2
endmcro

MAIN:   mov #5, r1
        m1
        stop

### Output (excerpt from .ob)
010 A  0005
102 A  2002
F00 A

## 🚀 How to Build & Run
### Build
```
make
```
### Run
```
./assembler file.as
```

## ⚠ Error Handling
The assembler detects and reports:
* Undefined labels
* Illegal addressing modes
* Invalid macro usage
* Syntax errors
* Duplicate label definitions
* Missing operands
* Memory overflow

## 🛠 Technologies
* C (ANSI C90)
* GCC (-ansi -Wall -pedantic)
* Linux / Ubuntu

## 📚 Course
Systems Programming Laboratory (20465)  
The Open University of Israel
