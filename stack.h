#ifndef Stack_h
#define Stack_H


#include "list.h"

typedef List Stack;

#define stack_create() createList()

#define stack_pop(stack) popFront(stack)

#define stack_push(stack, data) pushFront(stack, data)

#define stack_top(stack) firstList(stack)

#define stack_clean(stack) cleanList(stack)


#endif /* Stack.h */