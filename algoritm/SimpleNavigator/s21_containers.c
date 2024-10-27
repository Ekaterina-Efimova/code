#include "common.h"

int init(List** list, int type);

/**
 * Создание пустого стека
 * @param list Указатель на контейнер
 * @return EXIT_SUCCESS=0 или EXIT_FAILURE=1
 */
int stack(List** list) { return init(list, 's'); }

/**
 * Создание пустой очереди
 * @param list Указатель на контейнер
 * @return EXIT_SUCCESS=0 или EXIT_FAILURE=1
 */
int queue(List** list) { return init(list, 'q'); }

/**
 * Вспомогательная функция инициализации контейнера
 * @param list Двойной указатель на контейнер
 * @param type Тип контейнера `s` или `q`
 * @return EXIT_SUCCESS=0 или EXIT_FAILURE=1
 */
int init(List** list, int type) {
  int error = EXIT_SUCCESS;
  if ((*list = calloc(1, sizeof(List))) != NULL) {
    (*list)->type = type;
  } else {
    error = EXIT_FAILURE;
  }
  return error;
}

/**
 * Добавление элемента в контейнер
 * @param list Указатель на контейнер
 * @param value Добавляемое значение
 * @return EXIT_SUCCESS=0 или EXIT_FAILURE=1
 */
int push(List* list, int value) {
  int error = EXIT_SUCCESS;
  Node* tmp;
  if (list) {
    if ((tmp = calloc(1, sizeof(Node))) != NULL) {
      tmp->value = value;
      tmp->prev = list->tail;
      if (list->tail) {
        list->tail->next = tmp;
      }
      if (list->head == NULL) {
        list->head = tmp;
      }
      list->tail = tmp;
    } else {
      error = EXIT_FAILURE;
    }
  } else {
    error = EXIT_FAILURE;
  }
  return error;
}

/**
 * Получение элемента с его последующим удалением
 * @param list Указатель на контейнер
 * @param error EXIT_SUCCESS=0 или EXIT_FAILURE=1
 * @return Значение элемента
 */
int pop(List* list, int* error) {
  *error = EXIT_SUCCESS;
  int result = 0;
  Node* tmp = NULL;
  if (list && list->head && list->type == 'q') {
    tmp = list->head;
    if (tmp->next) {
      tmp->next->prev = NULL;
    } else {
      list->tail = NULL;
    }
    list->head = tmp->next;
    result = tmp->value;
    free(tmp);
  } else if (list && list->tail && list->type == 's') {
    tmp = list->tail;
    if (tmp->prev) {
      tmp->prev->next = NULL;
    } else {
      list->head = NULL;
    }
    list->tail = tmp->prev;
    result = tmp->value;
    free(tmp);
  } else {
    *error = EXIT_FAILURE;
  }
  return result;
}

/**
 * Получение элемента из стека без его удаления
 * @param list Указатель на контейнер
 * @param error EXIT_SUCCESS=0 или EXIT_FAILURE=1
 * @return Значение элемента
 */
int top(const List* const list, int* error) {
  *error = EXIT_SUCCESS;
  int result = 0;
  if (list && list->tail) {
    result = list->tail->value;
  } else {
    *error = EXIT_FAILURE;
  }
  return result;
}

/**
 * Получение первого элемента из очереди без его удаления
 * @param list Указатель на контейнер
 * @param error EXIT_SUCCESS=0 или EXIT_FAILURE=1
 * @return Значение элемента
 */
int front(const List* const list, int* error) {
  *error = EXIT_SUCCESS;
  int result = 0;
  if (list && list->head) {
    result = list->head->value;
  } else {
    *error = EXIT_FAILURE;
  }
  return result;
}

/**
 * Получение последнего элемента из очереди без его удаления
 * @param list Указатель на контейнер
 * @param error EXIT_SUCCESS=0 или EXIT_FAILURE=1
 * @return Значение элемента
 */
int back(const List* const list, int* error) { return top(list, error); }

/**
 * Удаление контейнера
 * @param list двойной Указатель на контейнер
 */
void destroy(List** list) {
  if (*list) {
    Node* tmp = (*list)->head;
    while (tmp) {
      Node* tmp_free = tmp;
      tmp = tmp->next;
      free(tmp_free);
    }
    free(*list);
    *list = NULL;
  }
}