/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 14:34:27 by mfilahi           #+#    #+#             */
/*   Updated: 2018/12/13 14:49:15 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		parse_op_2(char *op, int *flag)
{
	if (*op == 'a')
		*flag |= f_seedots;
	else if (*op == '@')
		*flag |= (*flag & f_list) ? f_xatt : 0;
	else if (*op == 'R')
		*flag |= f_recu;
	else if (*op == 'r')
		*flag |= f_rev;
	else if (*op == 't')
		*flag |= f_time_m;
	else if (*op == 's')
		*flag |= f_blocksz;
	else if (*op == 'f')
	{
		*flag |= f_no_sort;
		*flag |= f_seedots;
		*flag |= f_rev;
	}
	else
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putcharl_fd(*op, 2);
		ft_putendl_fd("usage: ft_ls [-ORalrt@1] [file ...]", 2);
		exit(FAILURE);
	}
}

void		parse_op_1(char *op, int *flag)
{
	while (*op)
	{
		if (*op == 'O')
			*flag |= f_flags;
		else if (*op == 'g')
		{
			*flag |= f_no_owner;
			*flag |= f_list;
		}
		else if (*op == 'o')
		{
			*flag |= f_no_group;
			*flag |= f_list;
		}
		else if (*op == '1')
		{
			*flag |= f_one;
			*flag &= ~f_list;
		}
		else if (*op == 'l')
			*flag |= (*flag & f_one) ? 0 : f_list;
		else
			parse_op_2(op, flag);
		op++;
	}
}

char		**test_file_exist(char **argv, int argc, int start)
{
	char	**files;
	int		i;

	i = 0;
	if ((files = (char **)malloc(sizeof(char *))) == NULL)
		return (NULL);
	while (start <= argc - 1)
	{
		if (opendir(argv[start]) == NULL)
			error_msg(argv[start]);
		else
			files[i++] = ft_strdup(argv[start]);
		start++;
	}
	merge_sort(files, 0, i - 1);
	files[i] = 0;
	if (i == 0)
		exit(DANGER);
	return (files);
}

void		param_files(char **files, int flag, char **argv, int argc)
{
	int i;

	i = 0;
	files = test_file_exist(argv, argc, i);
	while (files[i])
	{
		ft_printf("%s:\n", files[i]);
		ft_ls(files[i], flag);
		if (files[i + 1] != NULL)
			ft_printf("\n");
		i++;
	}
}

void		free_memory(t_file **folders, t_file **files, t_dirent **dp)
{
	t_file *tmp;

	while ((tmp = *folders) != NULL)
	{
		*folders = (*folders)->next;
		free(tmp);
	}
	while ((tmp = *files) != NULL)
	{
		*files = (*files)->next;
		free(tmp);
	}
	free(*dp);
	init_stat(&g_lenstat);
}
