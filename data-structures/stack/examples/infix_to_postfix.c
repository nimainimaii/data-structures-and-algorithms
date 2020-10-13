#include <assert.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char stack[100];
int top = -1;

bool is_empty() {
    if (top == -1) {
        return true;
    }
    return false;
}

bool is_operator(char c) {
    if (c == '^' || c == '+' || c == '*' || c == '-' || c == '/') {
        return true;
    }
    return false;
}

bool is_operand(char c) {
    if (c >= 'a' && c <= 'z') {
        return true;
    }
    if (c >= 'A' && c <= 'Z') {
        return true;
    }
    return false;
}

int pres(char c) {
    assert(is_operator(c));
    if (c == '^') {
        return 2;
    } else if (c == '/' || c == '*') {
        return 1;
    } else {
        return 0;
    }
}

void push(char c) {
    stack[++top] = c;
}

void pop() {
    if (top == -1) {
        printf("Popping from empty stack!");
        return;
    } else {
        top--;
    }
}

char peek() {
    if (top == -1) {
        printf("Peeking empty stack!");
        return '\0';
    }
    return stack[top];
}

void print_postfix(char* infix) {
    int l = 0;
    char* c = infix;
    while (*c != '\0') {
        l++;
        c++;
    }
    printf("Postfix expression is: ");
    for (int i = 0; i < l; i++) {
        if (is_operand(infix[i])) {
            printf("%c", infix[i]);
        } else if (is_operator(infix[i])) {
            while (!is_empty() && peek() != '(' &&
                   pres(peek()) >= pres(infix[i])) {
                printf("%c", peek());
                pop();
            }
            push(infix[i]);
        } else if (infix[i] == '(') {
            push(infix[i]);
        } else if (infix[i] == ')') {
            while (!is_empty() && peek() != '(') {
                printf("%c", peek());
                pop();
            }
            pop();
        }
    }
    while (!is_empty()) {
        printf("%c", peek());
        pop();
    }
}

int main() {
    char infix[] = "";
    scanf("%s", infix);
    printf("%d", strlen(infix));
    return 0;
}
