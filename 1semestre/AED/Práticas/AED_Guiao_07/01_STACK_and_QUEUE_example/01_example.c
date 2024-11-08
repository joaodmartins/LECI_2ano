//
// TO DO : desenvolva um algoritmo para verificar se um numero inteiro positivo
//         e uma capicua
//         Exemplos: 12321 e uma capiacua, mas 123456 nao e
//         USE uma PILHA DE INTEIROS (STACK) e uma FILA DE INTEIROS (QUEUE)
//
// TO DO : design an algorithm to check if the digits of a positive decimal
//         integer number constitue a palindrome
//         Examples: 12321 is a palindrome, but 123456 is not
//         USE a STACK of integers and a QUEUE of integers
//

#include <stdio.h>

#include "IntegersQueue.h"
#include "IntegersStack.h"

int isPalindrome(int number) {
    Stack* stack = StackCreate(20);
    Queue* queue = QueueCreate(20);

    int temp = number;

    while (temp > 0) {
        int digit = temp % 10;
        StackPush(stack, digit);
        QueueEnqueue(queue, digit);
        temp /= 10;
    }

    while (!StackIsEmpty(stack)) {
        if (StackPop(stack) != QueueDequeue(queue)) {
            StackDestroy(&stack);
            QueueDestroy(&queue);
            return 0;
        }
    }

    StackDestroy(&stack);
    QueueDestroy(&queue);
    return 1;
}

int main(void) {
    int number;
    printf("Digite um numero inteiro positivo: ");
    scanf("%d", &number);

    if (number < 0) {
        printf("Por favor insira um numero inteiro positivo");
        return 1;
    }

    if (isPalindrome(number)) {
        printf("E uma capicua");

    } else {
        printf("Nao e uma capicua");
    }

    return 0;
}