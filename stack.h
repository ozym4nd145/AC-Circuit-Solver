#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct stack
{
	int id;
	struct stack* next;
} stack;

stack* push(stack* lst,int data);
stack* pop(stack* lst);

#endif