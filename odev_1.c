#include <stdio.h>
#define SIZE 100

typedef struct {
    int top;
    int array[SIZE];
} STACK;

void init(STACK *stack) {
    stack->top = 0;
}

int isFull(STACK *stack) {
    if(stack->top == SIZE)
        return 1;
    else
        return 0;
}

int isEmpty(STACK *stack) {
    if(stack->top == 0)
        return 1;
    else
        return 0;
}
void push(STACK *stack, int value) {
    if(isFull(stack))
        printf("Stack dolu push islemi yapilamiyor");
    else {
        stack->array[stack->top] = value;
        stack->top++;
    }

}
int pop(STACK *stack) {
    if(isEmpty(stack)) {
        printf("Stack bos pop islemi yapilamiyor");
        return -1;
    } else {
        stack->top--;
        return stack->array[stack->top];
    }
}


int main() {
    STACK stack;
    int value;
    init(&stack);
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    value = pop(&stack);
    printf("%d\n", value);
    value = pop(&stack);
    printf("%d\n", value);
    value = pop(&stack);
    printf("%d\n", value);
    return 0;
}