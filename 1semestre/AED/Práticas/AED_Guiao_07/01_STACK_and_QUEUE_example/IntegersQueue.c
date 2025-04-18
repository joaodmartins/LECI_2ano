//
// Algoritmos e Estruturas de Dados --- 2024/2025
//
// Joaquim Madeira, Joao Manuel Rodrigues - June 2021, November 2023
//
// Integers queue (First In First Out) implementation based on a circular array

#include "IntegersQueue.h"

#include <assert.h>
#include <stdlib.h>

struct _IntegersQueue {
  int max_size;  // maximum Queue size
  int cur_size;  // current Queue size
  int head;
  int tail;
  int* data;  // the Queue data (integers stored in an array)
};

// PRIVATE auxiliary function

static int increment_index(const Queue* q, int i) {
  return (i + 1 < q->max_size) ? i + 1 : 0;
}

// PUBLIC functions

Queue* QueueCreate(int size) {
  assert(size >= 1 && size <= 1000000);
  Queue* q = (Queue*)malloc(sizeof(Queue));
  if (q == NULL) abort();

  q->max_size = size;
  q->cur_size = 0;

  q->head = 1;  // cur_size = tail - head + 1
  q->tail = 0;

  q->data = (int*)malloc(size * sizeof(int));
  if (q->data == NULL) {
    free(q);
    abort();
  }
  return q;
}

void QueueDestroy(Queue** p) {
  assert(*p != NULL);
  Queue* q = *p;
  free(q->data);
  free(q);
  *p = NULL;
}

void QueueClear(Queue* q) {
  q->cur_size = 0;
  q->head = 1;  // cur_size = tail - head + 1
  q->tail = 0;
}

int QueueSize(const Queue* q) { return q->cur_size; }

int QueueIsFull(const Queue* q) { return (q->cur_size == q->max_size); }

int QueueIsEmpty(const Queue* q) { return (q->cur_size == 0); }

int QueuePeek(const Queue* q) {
  assert(q->cur_size > 0);
  return q->data[q->head];
}

void QueueEnqueue(Queue* q, int i) {
  assert(q->cur_size < q->max_size);
  q->tail = increment_index(q, q->tail);
  q->data[q->tail] = i;
  q->cur_size++;
}

int QueueDequeue(Queue* q) {
  assert(q->cur_size > 0);
  int old_head = q->head;
  q->head = increment_index(q, q->head);
  q->cur_size--;
  return q->data[old_head];
}
