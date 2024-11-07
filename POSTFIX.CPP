#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100


int top = -1;
char stack[MAX];


void push(char c) {
    if (top == MAX - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack[top--];
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    return 0;
}

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int is_digit(char c) {
    return (c >= '0' && c <= '9');
}


void infix_to_postfix(char *infix, char *postfix) {
    int k = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        if (is_digit(infix[i])) {
            postfix[k++] = infix[i]; 
        } else if (infix[i] == '(') {
            push(infix[i]);  // Push '(' to stack
        } else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = pop(); 
            }
            pop();  // Pop '('
        } else if (is_operator(infix[i])) {
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i])) {
                postfix[k++] = pop();
            }
            push(infix[i]);
        }
    }
    
   
    while (top != -1) {
        postfix[k++] = pop();
    }
    postfix[k] = '\0'; 
}

int evaluate_postfix(char *postfix) {
    int stack[MAX], top = -1;
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (is_digit(postfix[i])) {
            stack[++top] = postfix[i] - '0';  
        } else if (is_operator(postfix[i])) {
            int b = stack[top--];
            int a = stack[top--];
            int result;
            switch (postfix[i]) {
 case '+': result = a + b; break;
 case '-': result = a - b; break;
 case '*': result = a * b; break;
 case '/': result = a / b; break;
}
stack[++top] = result;  // Push result back to stack
 }
 }
 return stack[top];  // Final result
}

int main() {
char infix[MAX], postfix[MAX];
printf("Enter infix expression: ");
fgets(infix, sizeof(infix), stdin);
infix[strcspn(infix, "\n")] = 0;  // Remove newline character
infix_to_postfix(infix, postfix);
printf("Postfix Expression: %s\n", postfix);
int result = evaluate_postfix(postfix);
printf("Result: %d\n", result);
    
    return 0;
}
