/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortLinked.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 11:41:34 by mfilahi           #+#    #+#             */
/*   Updated: 2018/12/13 14:47:47 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/ft_ls.h"

void	partition(t_file *head, t_file **front, t_file **back)
{
	t_file *fast;
	t_file *slow;

	if (head == NULL || head->next == NULL)
	{
		*front = head;
		*back = NULL;
	}
	else
	{
		slow = head;
		fast = head->next;
		while (fast != NULL)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front = head;
		*back = slow->next;
		slow->next = NULL;
	}
}

t_file	*merged_lists(t_file *a, t_file *b)
{
	t_file *mergedList;

	mergedList = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (ft_strcmp(a->d_name, b->d_name) <= 0)
	{
		mergedList = a;
		mergedList->next = mergedLists(a->next, b);
	}
	else
	{
		mergedList = b;
		mergedList->next = mergedLists(a, b->next);
	}
	return (mergedList);
}

t_file	*merged_lists_time(t_file *a, t_file *b)
{
	t_file *mergedList;

	mergedList = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (ft_timecmp(a->f_stat.smtime, b->f_stat.smtime) == 0)
	{
		mergedList = a;
		mergedList->next = mergedLists_time(a->next, b);
	}
	else
	{
		mergedList = b;
		mergedList->next = mergedLists_time(a, b->next);
	}
	return (mergedList);
}

void	g_merge_sort(t_file **source, int flag)
{
	t_file *head;
	t_file *a;
	t_file *b;

	b = NULL;
	a = NULL;
	head = *source;
	if (head == NULL || head->next == NULL)
		return ;
	partition(head, &a, &b);
	g_merge_sort(&a, flag);
	g_merge_sort(&b, flag);
	if (flag & f_time_m)
		*source = merged_lists_time(a, b);
	else
		*source = merged_lists(a, b);
}

void	ft_push(struct s_file **head_ref,
			t_dirent *dp, t_stat stat, char *path)
{
	t_file	*new_node;

	if (!(new_node = (struct s_file*)malloc(sizeof(t_file))))
		exit(DANGER);
	new_node->d_name = ft_stralloc(dp->d_name, dp->d_namlen);
	new_node->f_stat = stat;
	new_node->path = ft_strdup(path);
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}
