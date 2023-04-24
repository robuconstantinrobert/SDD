#include <stdio.h>
#include <stdlib.h>

typedef struct DequeNode {
    int data;
    struct DequeNode* prev;
    struct DequeNode* next;
} DequeNode;

typedef struct Deque {
    DequeNode* front;
    DequeNode* rear;
} Deque;

Deque* createDeque() {
    Deque* deque = (Deque*)malloc(sizeof(Deque));
    deque->front = NULL;
    deque->rear = NULL;
    return deque;
}

int isEmpty(Deque* deque) {
    return deque->front == NULL;
}

void pushFront(Deque* deque, int data) {
    DequeNode* node = (DequeNode*)malloc(sizeof(DequeNode));
    node->data = data;
    node->prev = NULL;
    node->next = deque->front;
    if (isEmpty(deque)) {
        deque->rear = node;
    }
    else {
        deque->front->prev = node;
    }
    deque->front = node;
}

void pushRear(Deque* deque, int data) {
    DequeNode* node = (DequeNode*)malloc(sizeof(DequeNode));
    node->data = data;
    node->prev = deque->rear;
    node->next = NULL;
    if (isEmpty(deque)) {
        deque->front = node;
    }
    else {
        deque->rear->next = node;
    }
    deque->rear = node;
}

int popFront(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return -1;
    }
    int data = deque->front->data;
    DequeNode* temp = deque->front;
    deque->front = deque->front->next;
    if (deque->front == NULL) {
        deque->rear = NULL;
    }
    else {
        deque->front->prev = NULL;
    }
    free(temp);
    return data;
}

int popRear(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return -1;
    }
    int data = deque->rear->data;
    DequeNode* temp = deque->rear;
    deque->rear = deque->rear->prev;
    if (deque->rear == NULL) {
        deque->front = NULL;
    }
    else {
        deque->rear->next = NULL;
    }
    free(temp);
    return data;
}

void printDeque(Deque* deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return;
    }
    DequeNode* current = deque->front;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    Deque* deque = createDeque();
    pushFront(deque, 2);
    pushFront(deque, 1);
    pushRear(deque, 3);
    pushRear(deque, 4);
    printDeque(deque);
    printf("Pop front: %d\n", popFront(deque));
    printf("Pop rear: %d\n", popRear(deque));
    printDeque(deque);
    return 0;
}