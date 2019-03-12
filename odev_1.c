#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

typedef struct {
    int top;
    int array[SIZE];
} INTSTACK;

typedef struct {
    int top;
    char array[SIZE];
} CHARSTACK;

void initInt(INTSTACK *stack) {
    stack->top = 0;
}
void initChar(CHARSTACK *stack) {
    stack->top = 0;
}

int isFullInt(INTSTACK *stack) {
    if(stack->top == SIZE)
        return 1;
    else
        return 0;
}
int isFullChar(CHARSTACK *stack) {
    if(stack->top == SIZE)
        return 1;
    else
        return 0;
}

int isEmptyInt(INTSTACK *stack) {
    if(stack->top == 0)
        return 1;
    else
        return 0;
}
int isEmptyChar(CHARSTACK *stack) {
    if(stack->top == 0)
        return 1;
    else
        return 0;
}

void pushInt(INTSTACK *stack, int value) {
    if(isFullInt(stack))
        printf("Stack dolu push islemi yapilamiyor\n");
    else {
        stack->array[stack->top] = value;
        stack->top++;
    }

}
void pushChar(CHARSTACK *stack, char value) {
    if(isFullChar(stack))
        printf("Stack dolu push islemi yapilamiyor\n");
    else {
        stack->array[stack->top] = value;
        stack->top++;
    }

}
int popInt(INTSTACK *stack) {
    if(isEmptyInt(stack)) {
        printf("Stack bos pop islemi yapilamiyor\n");
        return -1;
    } else {
        stack->top--;
        return stack->array[stack->top];
    }
}
char popChar(CHARSTACK *stack) {
    if(isEmptyChar(stack)) {
        printf("Stack bos pop islemi yapilamiyor\n");
        return -1;
    } else {
        stack->top--;
        return stack->array[stack->top];
    }
}

int peekInt(INTSTACK *stack, int *x) {
    if(isEmptyInt(stack)) {
        printf("Stack bos.");
        return 0;
    } else {
        int tmp;
        tmp = stack->top - 1;
        *x = stack->array[tmp];
        return 1;
    }
}
int peekChar(CHARSTACK *stack, char *x) {
    if(isEmptyChar(stack)) {
        printf("Stack bos.");
        return 0;
    } else {
        int tmp;
        tmp = stack->top - 1;
        *x = stack->array[tmp];
        return 1;
    }
}
int stringToInt(char *string) {
    int result;
    result = atoi(string);
    return result;
}

int main() {
    INTSTACK stackI;
    CHARSTACK stackC;
    initInt(&stackI);
    initChar(&stackC);
    int i = 0, j = 0;
    char k, l, *ptr;
    char *test = "12 * (4 + 3 - 16 / 9) - 5";
    ptr = test;
    while(test[i]) {
        sscanf(ptr, "%c ", &k);
        switch (k)
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                j = 1;
                sscanf(ptr, "%d", &i);
                printf("%d", i);
                pushInt(&stackI, i);
                if(i/100 > 0) {
                    ptr += 2;
                    i += 2;
                }
                else if(i/10 > 0) {
                    ptr += 1;
                    i++;
                }
                break;
            case '*':
            case '-':
            case '+':
            case '/':
            case '(':
            case ')':
                pushChar(&stackC, k);
                printf("%c", k);
                break;
            default:
                break;
        }
        i++;
        ptr++;
    }
    printf("\nChar stacki\n");
    for(i=stackC.top-1; i >= 0; i--) {
        printf("%c\n", stackC.array[i]);
    }
    printf("Int stacki\n");
    for(i=stackI.top-1; i >= 0; i--) {
        printf("%d\n", stackI.array[i]);
    }
    printf("\n");
    return 0;
}