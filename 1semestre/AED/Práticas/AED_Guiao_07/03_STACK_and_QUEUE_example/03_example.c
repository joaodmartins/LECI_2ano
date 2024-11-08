# include "PointersQueue.h"
#include "PointersStack.h"
#include "Date.h"
#include "Person.h"

#include<stdio.h>

int main(void) {
    Queue* queue = QueueCreate(5);
    Stack* stack = StackCreate(5);

    Date* yesterday = DateCreate(2024, 11, 07);
    Date* today = DateCreate(2024, 11, 08);
    Date* tomorow = DateCreate(2024, 11, 09);

    QueueEnqueue(queue, yesterday);
    QueueEnqueue(queue, today);
    QueueEnqueue(queue, tomorow);
    
    StackPush(stack, yesterday);
    StackPush(stack, today);
    StackPush(stack, tomorow);

    

    QueueDestroy(&queue);
    StackDestroy(&stack);
    DateDestroy(&yesterday);
    DateDestroy(&today);
    DateDestroy(&tomorow);
    return 0;
}