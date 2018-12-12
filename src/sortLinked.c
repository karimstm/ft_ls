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

	}

}



t_file *mergedLists (t_file *a, t_file *b)
{
	t_file *mergedList = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);

	if (ft_strcmp(a->d_name, b->d_name) <= 0)
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

t_file *mergedLists_time(t_file *a, t_file *b)
{
	t_file *mergedList = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);

	if (ft_timecmp(a->f_stat.smtime, b->f_stat.smtime) == 0)
	{
		mergedList = a;
		mergedList->next = mergedLists_time(a->next, b);
	}else
	{
		mergedList = b;
		mergedList->next = mergedLists_time(a, b->next);
	}
	return (mergedList);
}


void	mergeSort(t_file **source, int flag)
{
	t_file *head = *source;
	t_file *a = NULL;
	t_file *b = NULL;

	if (head == NULL || head->next == NULL)
		return ;
	partition(head, &a, &b);
	mergeSort(&a, flag);
	mergeSort(&b, flag);
	if (flag & f_time_m)
		*source = mergedLists_time(a, b);
	else
		*source = mergedLists(a, b);
}

void ft_push(struct s_file** head_ref, t_dirent *dp, t_stat stat,  char *path) 
{ 

	//printf("|%s|\n", dp->d_name);
	t_file* new_node = (struct s_file*) malloc(sizeof(t_file));
	new_node->d_name = ft_stralloc(dp->d_name, dp->d_namlen);
	new_node->f_stat = stat;
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
