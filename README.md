🧬 Logical Truth Table Generator (C)


















A high-performance, stack-based logical expression evaluator written in C. This tool parses infix logical expressions (containing A, B, C, and operators !, &, |) and generates a complete, dynamically-sized truth table.



🚀 Overview

In discrete mathematics, truth tables are the foundation of propositional logic. This project implements a Mini-Compiler pipeline:





Lexical Scanning: Detecting active propositions



Parsing: Converting Infix notation to Reverse Polish Notation (RPN/Postfix) using the Shunting-Yard Algorithm



Evaluation: Computing the boolean result for all (2^n) possible states using a Stack-based Evaluator



🧩 Supported Grammar

Variables





A, B, C (case-sensitive)

Operators





! : NOT (unary)



& : AND (binary)



| : OR (binary)

Parentheses





( ) for grouping

Expression

An expression may contain variables, operators, and parentheses, for example:





A & B



!C



A | (B & !C)



(A & B) | !C



Whitespace is allowed anywhere.



🛠 Features





Dynamic Row Generation
Automatically detects if you used 1, 2, or 3 variables and generates (2^1), (2^2), or (2^3) rows accordingly.



Operator Precedence
Correctly handles ! (NOT) > & (AND) > | (OR).



Parentheses Support
Deeply nested sub-expressions are handled via Shunting-Yard logic.



Memory Efficient
Uses fixed-size stacks and bit-manipulation for state generation.



📊 Flowchart

graph TD
    A[User Input: Infix Expression] --> B{Shunting-Yard Parser}
    B --> C[Postfix Expression - RPN]
    C --> D[Truth Table Engine]
    D --> E[Bit-Manipulation for States]
    E --> F[Stack-based Evaluator]
    F --> G[Formatted ASCII Table Output]




🧠 Technical Deep Dive

1. The Shunting-Yard Algorithm

The core of the parser. It uses an operator stack to re-order the expression based on precedence rules.

Input: A | (B & !C)
Output (Postfix/RPN): A B C ! & |

How it works (high level)





Variables are sent directly to the output stream (postfix).



Operators are pushed/popped based on precedence:





! has highest precedence



& next



| lowest



Parentheses control grouping by forcing stack operations until the matching ( is found.

This ensures that the postfix expression preserves the same semantics as the original infix expression.



2. Postfix Evaluation (Stack-based)

Unlike infix, postfix doesn’t need parentheses. We push operands (A, B, C values) onto the stack.

When an operator is encountered:





! pops one operand, applies NOT, and pushes the result back.



& pops two operands, applies AND, and pushes the result back.



| pops two operands, applies OR, and pushes the result back.

At the end of evaluation, the stack contains the final boolean result for that row.



3. State Generation (Truth Values)

Instead of nested loops, we use a single loop from (0) to (2^n - 1).

Each bit of the loop index represents the truth value of a variable.

For example, with 3 variables (A, B, C) you can interpret the binary pattern as:





(0) (000) -> (A=0, B=0, C=0)



(1) (001) -> (A=0, B=0, C=1)



(2) (010) -> (A=0, B=1, C=0)



(3) (011) -> (A=0, B=1, C=1)



...



(7) (111) -> (A=1, B=1, C=1)

This compact approach keeps iteration simple and efficient.



💻 Compilation & Usage

Prerequisites





GCC or any standard C compiler

Build

gcc -O3 truth_table_gen.c -o truth_table


Run

./truth_table


Input

When running, you will be prompted to enter a logical expression using:





Variables: A, B, C



Operators: !, &, |



Parentheses: (, )



✨ Example Session

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

OperationComplexityParsing (Infix to Postfix)(O(N)) where (N) is expression lengthEvaluation per row(O(N))Total Table Generation(O(2^V \cdot N)) where (V) is number of variables

Where:





(V \in {1,2,3})



(2^V) is the number of truth table rows



🧾 Notes / Assumptions





Expression parsing follows standard logical precedence: [ ! ;>; & ;>; | ]



! is unary and binds strongly.



Parentheses override precedence as expected.



👨‍💻 Author

Parsa
Computer Engineering Student | AI & Mathematics Enthusiast

"In logic, there are no accidents."



📄 License

© 2026 Parsa - Open Source under MIT License.
