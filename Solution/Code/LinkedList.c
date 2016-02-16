
/*
 * Implement a Queue & provide Enqueue and Dequeue operations
 *
 * */
#include <string.h>
#include "DataTypes.h"


/* Adds the element in the Queue*/
void add (Node **head, Node *item)
{
	Node *current = *head;
	if(*head == NULL)
	{
		(*head) = item;
		(*head)->next = *head;
		(*head)->previous = *head;
		return;
	}

	while(current->next!=(*head))
	{
		current=current->next;
	}
	current->next=item;
	item->previous=current;
	item->next=(*head);
	(*head)->previous=item;
}

/* Deletes the node from the head and returns the pointer to the deleted function*/
Node *del(Node **head)
{
	Node *temp = (*head);
	if(*head == NULL)
		return NULL;

	if((*head)->next == (*head))
	{
		*head = NULL;
	}
	else
	{
		(*head)->previous->next=(*head)->next;
		(*head)->next->previous=(*head)->previous;
		(*head)=(*head)->next;
	}
	return(temp);
}


