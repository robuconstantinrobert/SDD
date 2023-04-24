#include <stdio.h>
#include <stdlib.h>

typedef struct PriorityQueue {
    int* heap;
    int capacity;
    int size;
} PriorityQueue;

PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->heap = (int*)malloc(capacity * sizeof(int));
    pq->capacity = capacity;
    pq->size = 0;
    return pq;
}

int parent(int index) {
    return (index - 1) / 2;
}

int leftChild(int index) {
    return (2 * index) + 1;
}

int rightChild(int index) {
    return (2 * index) + 2;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void insert(PriorityQueue* pq, int value) {
    if (pq->size == pq->capacity) {
        printf("Priority queue is full\n");
        return;
    }
    pq->heap[pq->size] = value;
    int index = pq->size;
    while (index > 0 && pq->heap[index] > pq->heap[parent(index)]) {
        swap(&pq->heap[index], &pq->heap[parent(index)]);
        index = parent(index);
    }
    pq->size++;
}

int extractMax(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Priority queue is empty\n");
        return -1;
    }
    int max = pq->heap[0];
    pq->size--;
    pq->heap[0] = pq->heap[pq->size];
    int index = 0;
    while (index < pq->size) {
        int largest = index;
        int left = leftChild(index);
        int right = rightChild(index);
        if (left < pq->size && pq->heap[left] > pq->heap[largest]) {
            largest = left;
        }
        if (right < pq->size && pq->heap[right] > pq->heap[largest]) {
            largest = right;
        }
        if (largest == index) {
            break;
        }
        swap(&pq->heap[index], &pq->heap[largest]);
        index = largest;
    }
    return max;
}

void printPriorityQueue(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Priority queue is empty\n");
        return;
    }
    for (int i = 0; i < pq->size; i++) {
        printf("%d ", pq->heap[i]);
    }
    printf("\n");
}

int main() {
    PriorityQueue* pq = createPriorityQueue(5);
    insert(pq, 4);
    insert(pq, 1);
    insert(pq, 3);
    insert(pq, 2);
    printPriorityQueue(pq);
    printf("Extract max: %d\n", extractMax(pq));
    printf("Extract max: %d\n", extractMax(pq));
    printPriorityQueue(pq);
    return 0;
}