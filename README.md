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

## 🧠 Technical Deep Dive

1. Shunting-Yard Algorithm

Reorders infix expressions based on operator precedence, using an operator stack.

Input: A | (B & !C)

Output (Postfix): A B C ! & |

    Variables go directly to output (postfix).
    Operators are managed by precedence:
        ! (highest)
        &
        | (lowest)
    Parentheses ensure correct grouping.

2. Postfix Evaluation (Stack-based)

    Pushes variable values for each row.
    ! pops one value, applies NOT.
    &/| pop two values, apply AND/OR.

3. State Generation (Truth Values)

    Uses a single loop from 0 to 2^n - 1.
    Each bit of the loop index represents a variable’s truth value.

## 💻 Compilation & Usage

Prerequisites

    GCC or any standard C compiler

Build

                                                                    bash
gcc -O3 truth_table_gen.c -o truth_table

Run

                                                                    bash
./truth_table

When running, you will be prompted to enter a logical expression using:

    Variables: A, B, C
    Operators: !, &, |
    Parentheses: (, )

✨ Example Session

                                                                    text
Enter logical expression: (A & B) | !C

A B C | Result
-----------------
0 0 0 |   1
0 0 1 |   0
0 1 0 |   1
0 1 1 |   0
1 0 0 |   1
1 0 1 |   0
1 1 0 |   1
1 1 1 |   1

    The table dynamically includes only the variables present in your input expression.

🔬 Complexity Analysis
Operation 	Complexity
Parsing (Infix→Postfix) 	O(N)O(N) (expression length)
Evaluation per row 	O(N)O(N)
Total Table Generation 	O(2V⋅N)O(2V⋅N)

Where:

    VV = number of variables ∈{1,2,3}∈{1,2,3}
    2V2V = number of truth table rows

🧾 Notes / Assumptions

    Logical operator precedence: ! > & > |
    ! is unary and binds strongly
    Parentheses override precedence as expected

👨‍💻 Author

Parsa

Computer Engineering Student | AI & Mathematics Enthusiast

“In logic, there are no accidents.”
📄 License

© 2026 Parsa - Open Source under MIT License.
E --> F[Stack-based Evaluator]
F --> G[Formatted ASCII Table Output]
