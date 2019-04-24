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
        return 0;
    } else {
        int tmp;
        tmp = stack->top - 1;
        *x = stack->array[tmp];
        return 1;
    }
}
int stringToInt(char **ptr, int *i) {
    int num = 0;
    sscanf(*ptr, "%d", &num);
    if(num/100 > 0) {
        (*ptr) += 2;
        (*i) = (*i) + 2;
    }
    else if(num/10 > 0) {
        (*ptr)++;
        (*i)++;
    }
    return num;
}

void printStackCh(CHARSTACK *stack) {
    int i;
    printf("\n -- Char Stack -- \n");
    for(i=stack->top -1; i >= 0; i--)
        printf("\t%c\n", stack->array[i]);
}
void printStackInt(INTSTACK *stack) {
    int i;
    printf("\n -- Int Stack -- \n");
    for(i=stack->top -1; i >= 0; i--)
        printf("\t%d\n", stack->array[i]);
}
void printStacks(CHARSTACK *stackC, INTSTACK *stackI) {
    int i, spaceNumber = 40;
    printf("Sayi yigini :");
    for(i = 0; i < stackI->top; i++) {
        printf("%d ",stackI->array[i]);
        if(stackI->array[i] < 0)
            spaceNumber--;
        if(stackI->array[i] >= 1000 || stackI->array[i] <= -1000)
            spaceNumber -= 5;
        else if(stackI->array[i] >= 100 || stackI->array[i] <= -100)
            spaceNumber -= 4;
        else if(stackI->array[i] >= 10 || stackI->array[i] <= -10)
            spaceNumber -= 3;
        else
            spaceNumber -= 2;
    }
    for(i=0; i<spaceNumber; i++) {
        printf(" ");
    }
    printf(" Isaret yigini :");
    for(i = 0; i < stackC->top; i++) {
        printf("%c ", stackC->array[i]);
    }
    printf("\n");
}

int fourOperations(char sign, int num1, int num2) {
    switch (sign)
    {
        case '+': return num1 + num2; break;
        case '-': return num1 - num2; break;
        case '*': return num1 * num2; break;
        case '/': return num1 / num2; break;
        default:
            printf("Hatali aritmetik işaret !!!\n");
            exit(1);
            break;
    }
}

int main() {
    INTSTACK stackI;
    CHARSTACK stackC;
    initInt(&stackI);
    initChar(&stackC);
    int i = 0, num, num1, num2, result, isPeeked, finalResult;
    char *arithmeticExp, *ptr, symbl, operator, operatorFromS;
    arithmeticExp = (char*) malloc(sizeof(char)* 100);
    printf("Aritmetik ifade giriniz :");
    scanf("%[^\n]", arithmeticExp);
    ptr = arithmeticExp;
    while(arithmeticExp[i]) {
        sscanf(ptr, "%c", &symbl);
        switch (symbl)
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
                num = stringToInt(&ptr, &i);
                pushInt(&stackI, num);
                printStacks(&stackC, &stackI);
                break;
            case '+':
                isPeeked = peekChar(&stackC, &operator);
                if(operator == '(' || !isPeeked) {
                    pushChar(&stackC, symbl);
                    printStacks(&stackC, &stackI);
                } else {
                    do {
                        operatorFromS = popChar(&stackC);
                        num2 = popInt(&stackI);
                        num1 = popInt(&stackI);
                        result = fourOperations(operatorFromS, num1, num2);
                        pushInt(&stackI, result);
                        printStacks(&stackC, &stackI);
                        isPeeked = peekChar(&stackC, &operator);
                    }while(operator != '(' && isPeeked);
                    pushChar(&stackC, symbl);
                }
                break;
            case '-':
                isPeeked = peekChar(&stackC, &operator);
                if(operator == '(' || !isPeeked) {
                    pushChar(&stackC, symbl);
                    printStacks(&stackC, &stackI);
                } else {
                    do {
                        operatorFromS = popChar(&stackC);
                        num2 = popInt(&stackI);
                        num1 = popInt(&stackI);
                        result = fourOperations(operatorFromS, num1, num2);
                        pushInt(&stackI, result);
                        printStacks(&stackC, &stackI);
                        isPeeked = peekChar(&stackC, &operator);
                    }while(operator != '(' && isPeeked);
                    pushChar(&stackC, symbl);
                }
                break;
            case '*':
                isPeeked = peekChar(&stackC, &operator);
                if(operator == '+' || operator == '-' || operator == '(' || !isPeeked) {
                    pushChar(&stackC, symbl);
                    printStacks(&stackC, &stackI);
                } else {
                    do {
                        operatorFromS = popChar(&stackC);
                        num2 = popInt(&stackI);
                        num1 = popInt(&stackI);
                        result = fourOperations(operatorFromS, num1, num2);
                        pushInt(&stackI, result);
                        printStacks(&stackC, &stackI);
                        isPeeked = peekChar(&stackC, &operator);
                    }while((operator == '*' || operator == '/') && isPeeked);
                    pushChar(&stackC, symbl);
                }
                break;
            case '/':
                isPeeked = peekChar(&stackC, &operator);
                if(operator == '+' || operator == '-' || operator == '(' || !isPeeked) {
                    pushChar(&stackC, symbl);
                    printStacks(&stackC, &stackI);
                } else {
                    do {
                        operatorFromS = popChar(&stackC);
                        num2 = popInt(&stackI);
                        num1 = popInt(&stackI);
                        result = fourOperations(operatorFromS, num1, num2);
                        pushInt(&stackI, result);
                        printStacks(&stackC, &stackI);
                        isPeeked = peekChar(&stackC, &operator);
                    }while((operator == '*' || operator == '/') && isPeeked);
                    pushChar(&stackC, symbl);
                }
                break;
            case '(': pushChar(&stackC, symbl); printStacks(&stackC, &stackI); break;
            case ')':
                isPeeked = peekChar(&stackC, &operator);
                do {
                    operatorFromS = popChar(&stackC);
                    num2 = popInt(&stackI);
                    num1 = popInt(&stackI);
                    result = fourOperations(operatorFromS, num1, num2);
                    pushInt(&stackI, result);
                    printStacks(&stackC, &stackI);
                    isPeeked = peekChar(&stackC, &operator);
                }while((operator != '(') && isPeeked);
                popChar(&stackC);
                printStacks(&stackC, &stackI);
                break;
            default:
                break;
        }
        i++;
        ptr++;
    }
    isPeeked = peekChar(&stackC, &operator);
    do {
        operatorFromS = popChar(&stackC);
        num2 = popInt(&stackI);
        num1 = popInt(&stackI);
        result = fourOperations(operatorFromS, num1, num2);
        pushInt(&stackI, result);
        printStacks(&stackC, &stackI);
        isPeeked = peekChar(&stackC, &operator);
    }while(isPeeked);
    finalResult = popInt(&stackI);
    printf("\n-------------------------------\n\n");
    printf("Aritmetik ifadenin sonucu :%d\n", finalResult);
    printf("\n-------------------------------\n");
    return 0;
}