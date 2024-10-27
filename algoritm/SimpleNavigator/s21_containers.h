#ifndef A2_SIMPLENAVIGATOR_V1_0_1_S21_CONTAINERS_H
#define A2_SIMPLENAVIGATOR_V1_0_1_S21_CONTAINERS_H

typedef struct Node {
  int value;
  struct Node* prev;
  struct Node* next;
} Node;

typedef struct List {
  int type;
  Node* head;
  Node* tail;
} List;

int stack(List** list);
int queue(List** list);
int push(List* list, int value);
int top(const List* list, int* error);
int pop(List* list, int* error);
int front(const List* list, int* error);
int back(const List* list, int* error);
void destroy(List** list);

#endif  // A2_SIMPLENAVIGATOR_V1_0_1_S21_CONTAINERS_H