# 🧬 Logical Truth Table Generator (C)

![Language](https://img.shields.io/badge/Language-C-blue)
![Build](https://img.shields.io/badge/Build-Passing-brightgreen)
![Field](https://img.shields.io/badge/Field-Discrete_Mathematics-orange)
![License](https://img.shields.io/badge/License-MIT-lightgrey)

A high-performance, stack-based logical expression evaluator written in C.  
Parses infix logical expressions (with variables `A`, `B`, `C` and operators `!`, `&`, `|`), and generates a complete, dynamically-sized truth table.

---

## 🚀 Overview

In discrete mathematics, truth tables are the foundation of propositional logic.  
This project implements a **mini-compiler** pipeline:

1. **Lexical Scanning:** Detects propositions used in the input
2. **Parsing:** Converts infix notation to postfix (Reverse Polish Notation) using the **Shunting-Yard Algorithm**
3. **Evaluation:** Computes the boolean result for all \(2^n\) possible states using a stack-based evaluator

---

## 🧩 Supported Grammar

**Variables:**  
- `A`, `B`, `C` (case-sensitive)

**Operators:**  
- `!` : NOT (unary)  
- `&` : AND (binary)  
- `|` : OR (binary)  

**Parentheses:**  
- `( )` for grouping

**Examples:**
- `A & B`
- `!C`
- `A | (B & !C)`
- `(A & B) | !C`

> Whitespace is allowed anywhere

---

## 🛠 Features

- **Dynamic Row Generation:**  
  Automatically detects used variables and generates the corresponding \(2^n\) rows.

- **Operator Precedence:**  
  Correctly handles `!` > `&` > `|`.

- **Parentheses Support:**  
  Deeply nested sub-expressions are handled.

- **Memory Efficient:**  
  Uses stack and bit manipulation for fast state generation.

---

## 📊 Flowchart
```mermaid
graph TD
A[User Input: Infix Expression] --> B{Shunting-Yard Parser}
B --> C[Postfix Expression - RPN]
C --> D[Truth Table Engine]
D --> E[Bit-Manipulation for States]

© 2026 Parsa - Open Source under MIT License.
E --> F[Stack-based Evaluator]
F --> G[Formatted ASCII Table Output]
