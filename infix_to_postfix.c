#include <stdio.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char ch) {
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++top] = ch;
}

char pop() {
    if (top == -1)
        return '\0';

    return stack[top--];
}

char peek() {
    if (top == -1)
        return '\0';

    return stack[top];
}

int precedence(char ch) {
    if (ch == '^')
        return 3;
    if (ch == '*' || ch == '/' || ch == '%')
        return 2;
    if (ch == '+' || ch == '-')
        return 1;

    return 0;
}

int main() {
    char infix[MAX], postfix[MAX];
    int i, j = 0;
    char ch;

    printf("Enter infix expression: ");
    if (scanf("%99s", infix) != 1)
        return 1;

    for (i = 0; infix[i] != '\0'; i++) {
        ch = infix[i];

        if (isalnum((unsigned char)ch)) {
            postfix[j++] = ch;
        }
        else if (ch == '(') {
            push(ch);
        }
        else if (ch == ')') {
            while (top != -1 && peek() != '(') {
                postfix[j++] = pop();
            }

            if (peek() == '(')
                pop();
        }
        else if (ch == '+' || ch == '-' ||
                 ch == '*' || ch == '/' ||
                 ch == '%' || ch == '^') {

            while (top != -1 && peek() != '(' &&
                  (precedence(peek()) > precedence(ch) ||
                  (precedence(peek()) == precedence(ch)
                   && ch != '^'))) {
                postfix[j++] = pop();
            }

            push(ch);
        }
    }

    while (top != -1) {
        if (peek() == '(') {
            printf("Invalid expression\n");
            return 1;
        }
        postfix[j++] = pop();
    }

    postfix[j] = '\0';

    printf("Postfix expression: %s\n", postfix);

    return 0;
}
