/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:20:32 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/10 15:07:52 by amoutik          ###   ########.fr       */
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
		printf("%s\n", list_files->f_dp->d_name);
		list_files = list_files->next;	
	}
}


void	print_folders(t_file *folders, int flag)
{
	while (folders)
	{
		printf("\n%s:\n", folders->path);
		ft_ls(folders->path, flag);
		folders = folders->next;
	}
}

void	print_rev_files(t_file *list_files)
{
	if (list_files)
	{
		print_rev_files(list_files->next);
		printf("%s\n", list_files->f_dp->d_name);
	}		
}

void	Storage_into_ll(t_dirent *dp, t_file **files, t_file **folders, char *path)
{
	char *tmp;
	struct stat buf;
	t_stat mystat;
	if (dp->d_name[0] != '.')
	{	
		stat(dp->d_name, &buf);
		mystat.smtime = buf.st_mtime;
		ft_push(&(*files), dp, mystat, path);
		if (dp->d_type == DT_DIR && 
			!((dp->d_namlen == 1 && ft_strcmp(".", dp->d_name) == 0 ) 
				|| (dp->d_namlen == 2 &&  ft_strcmp("..", dp->d_name) == 0)))
		{
			tmp = ft_strjoin(path, "/");
			tmp = ft_strjoin(tmp, dp->d_name);
			ft_push(&(*folders), dp, mystat, tmp);
			free(tmp);
		}
	}
}


void	free_memory(t_file **folders, t_file **files, t_dirent **dp)
{
	free(*folders);
	free(*files);
	free(*dp);
}

void S_Byflags(t_file **files, t_file **folders, int flag)
{
	mergeSort(&(*files), flag);
	if (flag & f_recu)
	{
		print_files(*files);
		mergeSort(&(*folders), flag);
		print_folders(*folders, flag);
	}
	else if(flag & f_rev)
		print_rev_files(*files);
	else 
		print_files(*files);
}

int		ft_ls(char *path, int flag) 
{
	DIR *dir;
	t_dirent *dp;
	t_file *files;
	t_file *folders;

	if ((files = (t_file *)malloc(sizeof(t_file))) == NULL)
		return (0);
	files = NULL;
	folders = NULL;
	if (open_dir(path, &dir))
	{
		while (read_dir(dir, &dp))
			Storage_into_ll(dp, &files, &folders, path);
		S_Byflags(&files, &folders, flag);
		free_memory(&folders, &files, &dp);
		closedir(dir);
	}
	else
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
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
}

char	**test_file_exist(char **argv, int argc, int start)
{
	char **files;
	int i;

	i = 0;
	if ((files = (char **)malloc(sizeof(char *))) == NULL)
		return (NULL);
	while (start <= argc - 1)
	{
		if (opendir(argv[start]) == NULL)
		{
			ft_putstr_fd(ft_strjoin("ft_ls: ", argv[start]), 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else
			files[i++] = ft_strdup(argv[start]);
		start++;
	}
	Mergesort(files, 0, i - 1);
	files[i] = 0;
	if (i == 0)
		return (NULL);
	return (files);
}

int		main(int argc, char **argv)
{
	int i;
	int flag;
	char **files;
	i = 1;
	flag = 0;
	if (argc > 1)
	{
		while (i <= argc - 1 && argv[i][0] == '-')
			parse_op_1(++argv[i++], &flag);

		if (i <= argc - 1)
		{
			if (!(argc - 1 - i >= 1))
				ft_ls(argv[i++], flag);
			files = test_file_exist(argv, argc, i);
			i = 0;
			while (files[i])
			{	
				printf("%s:\n", files[i]);
				ft_ls(files[i], flag);
				if (files[i + 1] != NULL)
					printf("\n");
				i++;
			}
		}
		else	
			ft_ls(".", flag);
	}else
		ft_ls(".", flag);
	exit(SUCCESS);
}
