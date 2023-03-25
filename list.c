#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  
  List *list = NULL;
  list = (List *) malloc (sizeof(List));

  list->head = NULL;
  list->current = NULL;
  list->tail = NULL;
  
     return list;
}

void * firstList(List * list) {

  if (list->head == NULL)
  {
    return NULL;
  }
  
  list->current = list->head;
  return list->head->data;
}

void * nextList(List * list) {

  if (list->current == NULL)
  {
    return NULL;
  }

  if (list->current->next == NULL)
  {
    return NULL;
  }
  
  list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
  
  if (list->tail == NULL)
  {
    return NULL;
  }

  list->current = list->tail;
    return list->tail->data;
}

void * prevList(List * list) {

  if (list->current == NULL)
  {
    return NULL;
  }

  if (list->current->prev == NULL)
  {
    return NULL;
  }

  list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
 
  Node *nuevo = createNode(data);
  if (nuevo == NULL) return;

  if (list->head == list->tail)
  {
    list->head = nuevo;
    list->tail = nuevo;
    return;
  }

  if (list->head == NULL)
  {
    list->head = nuevo;
  }
  else
  {
    list->head->prev = nuevo;
    nuevo->next = list->head;
    list->head = nuevo;
  }
  
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  
  Node *nuevo = createNode(data);
  if (nuevo == NULL) return;

  if (list->current->next != NULL)
  {
    list->current->next->prev = nuevo;
    nuevo->next = list->current->next;
  }
  else
  {
    list->tail = nuevo;
  }

  list->current->next = nuevo;
  nuevo->prev = list->current;
  
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  
  void *aux = list->current->data;

  if (list->current->prev != NULL)
  {
    if (list->current->next != NULL)
    {
      list->current->prev = list->current->next->prev;
      list->current->next = list->current->prev->next;
    }
    else
    {
      list->current->prev->next = NULL;
    }
  }
  else
  {
    if (list->current->next != NULL)
    {
      list->current->next->prev = NULL;
    }
    else
    {
      free(list->current);
      return aux;
    }
  }

  if (list->current == list->head)
  {
    list->head = list->current->next;
  }

  if (list->current == list->tail)
  {
    list->tail = list->current->prev;
  }
  free(list->current);
    return aux;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}