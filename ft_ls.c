/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:20:32 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/10 09:32:41 by amoutik          ###   ########.fr       */
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
	t_stat mystat;
	struct stat buf;

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
				stat(dp->d_name, &buf);
				mystat.smtime = buf.st_mtime;
				ft_push(&files, dp, mystat, path);
				if (dp->d_type == DT_DIR)
				{
					tmp = ft_strjoin(path, "/");
					tmp = ft_strjoin(tmp, dp->d_name);
					ft_push(&folders, dp, mystat , tmp);
					free(tmp);
				}
			}
		}
		mergeSort(&files, flag);
		print_files(files);
		if (flag & f_recu)
		{	
			mergeSort(&folders, flag);
			print_folders(folders, flag);
		}
		free(folders);
		free(files);
		free(dp);
		closedir(dir);
	}
	else
	{
		ft_putstr_fd("ft_ls: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	//	exit(FAILURE);
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

int		test_file_existance(char *argv)
{
		if(opendir(argv) == NULL)
		{
			ft_putstr_fd("error\n", 2);
			return (0);
		}
	return (1);
}

int		main(int argc, char **argv)
{
	int i;
	int flag;
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
			while (i <= argc - 1)
			{	
				if (test_file_existance(argv[i]))
				{
					printf("%s:\n", argv[i]);
					ft_ls(argv[i], flag);
				 	if (argc - 1 - i >= 1)
						printf("\n");
				}
				i++;
			}
		}
		else	
			ft_ls(".", flag);
	}else
		ft_ls(".", flag);
	exit(SUCCESS);
}
