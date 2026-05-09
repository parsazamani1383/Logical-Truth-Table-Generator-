#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100   // maximum size for expression and stack

/*-------------------- STACK STRUCTURE --------------------*/
/* Simple stack structure used for operators in the
   infix→postfix conversion algorithm */
typedef struct {
    char items[MAX];
    int top;
} Stack;

/* Push element onto stack */
void push(Stack *s, char val) {
    s->items[++(s->top)] = val;
}

/* Pop element from stack */
char pop(Stack *s) {
    return s->items[(s->top)--];
}

/* Return the top element without removing it */
char peek(Stack *s) {
    return s->items[s->top];
}

/* Check if stack is empty */
int isEmpty(Stack *s) {
    return s->top == -1;
}

/*-------------------- OPERATOR PRIORITY --------------------*/
/*
Define logical operator precedence.

!  (NOT)  highest
&  (AND)
|  (OR)   lowest
*/
int precedence(char op) {
    if (op == '!') return 3;
    if (op == '&') return 2;
    if (op == '|') return 1;
    return 0;
}

/*-------------------- INFIX → POSTFIX --------------------*/
/*
Convert logical expression from infix notation
(example:  A&(B|C) )
to postfix notation
(example:  ABC|& )

This removes parentheses and makes evaluation easier.
Algorithm used: Shunting-yard.
*/
void infixToPostfix(char *infix, char *postfix) {

    Stack s;
    s.top = -1;

    int k = 0;

    for (int i = 0; infix[i]; i++) {

        char ch = infix[i];

        if (ch == ' ')
            continue;

        /* If character is a proposition (A,B,C) */
        if (isalpha(ch)) {
            postfix[k++] = ch;
        }

        /* If opening parenthesis */
        else if (ch == '(') {
            push(&s, ch);
        }

        /* If closing parenthesis */
        else if (ch == ')') {

            while (!isEmpty(&s) && peek(&s) != '(')
                postfix[k++] = pop(&s);

            pop(&s); // remove '('
        }

        /* If logical operator */
        else {

            while (!isEmpty(&s) &&
                   precedence(peek(&s)) >= precedence(ch)) {

                postfix[k++] = pop(&s);
            }

            push(&s, ch);
        }
    }

    /* pop remaining operators */
    while (!isEmpty(&s))
        postfix[k++] = pop(&s);

    postfix[k] = '\0';
}

/*-------------------- POSTFIX EVALUATION --------------------*/
/*
Evaluate the postfix logical expression using a stack.

Each row of the truth table provides values for A,B,C.
The expression is evaluated using those values.
*/
int evaluate(char *postfix, int A, int B, int C) {

    int stack[MAX];
    int top = -1;

    for (int i = 0; postfix[i]; i++) {

        char ch = postfix[i];

        /* Push variable value */
        if (ch == 'A') stack[++top] = A;
        else if (ch == 'B') stack[++top] = B;
        else if (ch == 'C') stack[++top] = C;

        /* Logical NOT */
        else if (ch == '!') {
            stack[top] = !stack[top];
        }

        /* Logical AND */
        else if (ch == '&') {
            int b = stack[top--];
            int a = stack[top--];
            stack[++top] = a && b;
        }

        /* Logical OR */
        else if (ch == '|') {
            int b = stack[top--];
            int a = stack[top--];
            stack[++top] = a || b;
        }
    }

    return stack[top];
}

/*-------------------- MAIN PROGRAM --------------------*/
int main() {

    char infix[MAX];
    char postfix[MAX];

    printf("Enter logical expression: ");
    fgets(infix, MAX, stdin);

    /* Remove newline from input */
    infix[strcspn(infix, "\n")] = 0;

    /* Detect which variables appear in expression */
    int hasA = 0, hasB = 0, hasC = 0;

    for (int i = 0; infix[i]; i++) {

        if (infix[i] == 'A') hasA = 1;
        if (infix[i] == 'B') hasB = 1;
        if (infix[i] == 'C') hasC = 1;
    }

    /* Convert expression to postfix */
    infixToPostfix(infix, postfix);

    /* Number of variables in expression */
    int varsCount = hasA + hasB + hasC;

    /* Number of rows in truth table = 2^n */
    int rows = 1 << varsCount;

    /* Print table header */
    if (hasA) printf("A ");
    if (hasB) printf("B ");
    if (hasC) printf("C ");

    printf("| Result\n");
    printf("-----------------\n");

    /* Generate truth table rows */
    for (int i = 0; i < rows; i++) {

        int valA = 0, valB = 0, valC = 0;

        int temp = i;

        /* Extract bits to assign values to variables */
        if (hasC) { valC = temp % 2; temp /= 2; }
        if (hasB) { valB = temp % 2; temp /= 2; }
        if (hasA) { valA = temp % 2; temp /= 2; }

        /* Print row values */
        if (hasA) printf("%d ", valA);
        if (hasB) printf("%d ", valB);
        if (hasC) printf("%d ", valC);

        /* Evaluate logical expression */
        int result = evaluate(postfix, valA, valB, valC);

        printf("|   %d\n", result);
    }

    return 0;
}
