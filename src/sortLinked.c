#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/ft_ls.h"

void partition(t_file *head, t_file **front, t_file **back){

	t_file *fast;
	t_file *slow;

	if (head == NULL || head->next == NULL){

		*front = head; // &a
		*back = NULL; // &b

	}else{

		slow = head;
		fast = head->next;

		while(fast != NULL){

			fast = fast->next;

			if(fast != NULL){

				slow = slow->next;
				fast = fast->next;

			}

		}

		*front = head; // a
		*back = slow->next; // b
		slow->next = NULL;
		//	printList(*front);
		//	printList(*back);

	}

}



t_file *mergedLists (t_file *a, t_file *b)
{
	t_file *mergedList = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);

	if (strcmp(a->f_name, b->f_name) <= 0)
	{
		mergedList = a;
		mergedList->next = mergedLists(a->next, b);
	}else
	{
		mergedList = b;
		mergedList->next = mergedLists(a, b->next);
	}
	return (mergedList);
}




void	mergeSort(t_file **source)
{
	t_file *head = *source;
	t_file *a = NULL;
	t_file *b = NULL;

	if (head == NULL || head->next == NULL)
		return ;
	partition(head, &a, &b);
	mergeSort(&a);
	mergeSort(&b);

	*source = mergedLists(a, b);
}

void ft_push(struct s_file** head_ref, char* new_data, size_t len, char *path) 
{ 
	t_file* new_node = (struct s_file*) malloc(sizeof(t_file)); 
	new_node->f_name  = ft_stralloc(new_data, len); 
	new_node->path = ft_strdup(path);
	new_node->next = (*head_ref); 
	(*head_ref)    = new_node; 
} 

/*
   void printList(t_file *head){

   t_file current = *head;
   while(current != NULL){
   printf("%s\n",current->f_name);
   current = current->next;
   }
   printf("\n");

   }
   */

/*
   int		main(void)
   {
   t_file head = NULL;
   t_file globalHead;
   t_file *list = &globalHead;

   push(&globalHead, &head, "karim");
   push(&globalHead, &head, "ahmed");
//push(&head, "said");
//push(&head, "banana");
//push(&head, "Apple");

printList(list);
mergeSort(list);
printList(list);
return (0);
}

*/
