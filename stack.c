#include "stack.h"

stack* push(stack* lst,int data)
{
	stack* new_stack = (stack*)malloc(sizeof(stack));
	new_stack->next=NULL;
	new_stack->id = data;
	
	if(lst != NULL)
	{
		new_stack->next = lst;
	}		
	return new_stack;
}

stack* pop(stack* lst)
{
	if(lst==NULL)
	{
		return NULL;
	}
	stack* new_stack = lst->next;
	free(lst);
	return	new_stack;
}
