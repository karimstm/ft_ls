/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:20:32 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/08 09:34:41 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/ft_ls.h"
#include <stdio.h>
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int		open_dir(char *path, DIR **dir)
{
	if ((*dir = opendir(path)) != NULL)
		return (1);
	return (0);
}

int		read_dir(DIR *dir, t_dirent **dp)
{
	if ((*dp = readdir(dir)) != NULL)
		return (1);
	return (0);	
}

void	print_files(t_file *list_files)
{
	while (list_files)
	{
		printf("%s\n", list_files->f_name);
		list_files = list_files->next;	
	}
}

void	add_file(t_file **list, char *d_name, size_t d_namlen)
{
	(*list)->f_name = ft_stralloc(d_name, d_namlen);
}

void	print_folders(t_file *folders, int flag)
{
	while (folders)
	{
		printf("\n%s:\n", folders->path);
		//if (!(ft_strcmp("./.", folders->f_name) == 0 || ft_strcmp("./..", folders->f_name) == 0))
		ft_ls(folders->path, flag);
		folders = folders->next;
	}
}

int		ft_ls(char *path, int flag) 
{
	DIR *dir;
	t_dirent *dp;
	t_file *files;
	char *tmp;
	t_file *folders;

	if ((files = (t_file *)malloc(sizeof(t_file))) == NULL)
		return (0);
	files = NULL;
	folders = NULL;
	if (open_dir(path, &dir))
	{
		while (read_dir(dir, &dp))
		{
			if (dp->d_name[0] != '.')
			{
				ft_push(&files, dp->d_name, dp->d_namlen, path);
				if (dp->d_type == DT_DIR)
				{
					tmp = ft_strjoin(path, "/");
					tmp = ft_strjoin(tmp, dp->d_name);
					ft_push(&folders, dp->d_name, dp->d_namlen, tmp);
					free(tmp);
				}
			}
		}
		mergeSort(&files);
		print_files(files);
		if (flag & f_recu)
		{	
			mergeSort(&folders);
			print_folders(folders, flag);
		}
		free(folders);
		free(files);
		free(dp);
		closedir(dir);
	}else
		printf("I can't access this dir\n");
	return (1);
}

void	parse_op_2(char *op, int *flag)
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
	else
	{
		ft_putstr_fd("ft_ls: illegal option -- ", 2);
		ft_putcharl_fd(*op, 2);
		ft_putendl_fd("usage: ft_ls [-ORalrt@1] [file ...]", 2);
		exit(FAILURE);
	}

}

void	parse_op_1(char *op, int *flag)
{
	if (*op == '-')
	{
		op++;
		while (*op)
		{
			if (*op == 'O')
				*flag |= f_flags;
			else if (*op == '1')
			{
				*flag |= f_one;
				*flag &= ~f_list;
			}
			else if (*op == 'l')
			{
				*flag |= (*flag & f_one) ? 0 : f_list;
			}else
				parse_op_2(op, flag);
			op++;
		}
	}else
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(op, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		//exit(FAILURE);
	}
}

int		main(int argc, char **argv)
{
	int i;
	int flag;
	i = 1;
	flag = 0;
	if (argc > 1)
	{
		while (i <= argc - 1)
		{
			parse_op_1(argv[i], &flag);
			i++;
		}
		ft_ls(argv[2], flag);
		//printf("%d\n", flag);
	}
	exit(SUCCESS);
}
