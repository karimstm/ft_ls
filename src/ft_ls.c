/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:20:32 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/12 17:14:49 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"
#include <stdio.h>
#include "ft_printf.h"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

t_stat lenstat;

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

void	init_stat(t_stat *stat)
{
	stat->hardlen = 0;
	stat->userlen = 0;
	stat->grouplen = 0;
	stat->sizelen = 0;
	stat->total_block = 0;
}

void	linkname(off_t st_size, char *path)
{
	char *linkname;

	linkname = malloc(st_size + 1);
    if (linkname == NULL)
		return ;
   if(readlink(path, linkname, st_size + 1))
	   ft_printf(" -> %s", linkname);
   free(linkname);
}


void	get_permissions(mode_t st_mode, char *path)
{
	char perm[20];
	ft_strmode(st_mode, perm, path);
	ft_printf("%s ", perm);
}

void	print_total(int flag)
{
	if (flag & f_list)
		ft_printf("total %lld\n", lenstat.total_block); 
}

void	print_files(t_file *list_files, int flag)
{
	struct stat sb;

	if (list_files)
	{
		if (flag & f_list)
		{
			if (flag & f_rev)
				print_files(list_files->next, flag);
			lstat(list_files->path, &sb);
			get_permissions(sb.st_mode, list_files->path);
			ft_printf("%*d ", lenstat.hardlen, sb.st_nlink);
			ft_printf("%-*s  ", (int)lenstat.userlen, (getpwuid(sb.st_uid))->pw_name);
			ft_printf("%-*s  ", (int)lenstat.grouplen, (getgrgid(sb.st_gid))->gr_name);
			ft_printf("%*lld ", lenstat.sizelen, sb.st_size);
			ft_printf("%s ", ft_strtrim(ctime(&sb.st_mtimespec.tv_sec)));	
		}
		if ((flag & f_rev) && !(flag & f_list))
			print_files(list_files->next, flag);
		ft_printf("%s", list_files->d_name);
		if (M_ISLNK(sb.st_mode) && (flag & f_list))
			linkname(sb.st_size, list_files->path);
		ft_printf("\n");
		if (flag & f_xatt)
				ft_getxattr(list_files->path);
		if (!(flag & f_rev))
			print_files(list_files->next, flag);
	}
	init_stat(&lenstat);
}


void	print_folders(t_file *folders, int flag)
{
	if (folders)
	{
		if (flag & f_rev)
			print_folders(folders->next, flag);
		ft_printf("\n%s:\n", folders->path);
		ft_ls(folders->path, flag);
		if (!(flag & f_rev))
			print_folders(folders->next, flag);
		init_stat(&lenstat);
	}
}

void	get_len(t_stat *stat, struct stat sb)
{
	stat->hardlen = MAX(stat->hardlen, number_len(sb.st_nlink));
	stat->userlen = MAX(stat->userlen, ft_strlen((getpwuid(sb.st_uid))->pw_name));
	stat->grouplen = MAX(stat->grouplen, ft_strlen((getgrgid(sb.st_gid))->gr_name));
	stat->sizelen = MAX(stat->sizelen, number_len(sb.st_size));
	stat->total_block += sb.st_blocks;
}

void	storage_into_ll(t_dirent *dp, t_file **files, t_file **folders, char *path)
{
	char *tmp;
	struct stat buf;
	t_stat mystat;
	char *newpath;

	newpath = ft_strjoin(path, "/");
	lstat(ft_strjoin(newpath, dp->d_name), &buf);
	mystat.smtime = buf.st_mtime;
	ft_push(&(*files), dp, mystat, ft_strjoin(newpath, dp->d_name));
	get_len(&lenstat, buf);
	if (dp->d_type == DT_DIR)
	{
		tmp = ft_strjoin(path, "/");
		tmp = ft_strjoin(tmp, dp->d_name);
		ft_push(&(*folders), dp, mystat, tmp);
		free(tmp);
	}
	free(newpath);
}

void	storage_with_dots(t_dirent *dp, t_file **files, t_file **folders, char *path)
{	
	char *tmp;
	struct stat buf;
	t_stat mystat;
	char *newpath;

	newpath = ft_strjoin(path, "/");
	lstat(ft_strjoin(newpath, dp->d_name), &buf);
	mystat.smtime = buf.st_mtime;
	if (buf.st_mode == 0)
		return ;
	ft_push(&(*files), dp, mystat, ft_strjoin(newpath, dp->d_name));
	get_len(&lenstat, buf);
	if (dp->d_type == DT_DIR && !(ft_strcmp(dp->d_name, ".") == 0 || ft_strcmp(dp->d_name, "..") == 0))
	{
		tmp = ft_strjoin(path, "/");
		tmp = ft_strjoin(tmp, dp->d_name);
		ft_push(&(*folders), dp, mystat, tmp);
		free(tmp);
	}
	free(newpath);
}


void	free_memory(t_file **folders, t_file **files, t_dirent **dp)
{
	free(*folders);
	free(*files);
	free(*dp);
}

void s_byflags(t_file **files, t_file **folders, int flag)
{
	mergeSort(&(*files), flag);
	print_total(flag);
	if (flag & f_recu)
	{

		print_files(*files, flag);
		mergeSort(&(*folders), flag);
		print_folders(*folders, flag);
	}
	else
		print_files(*files, flag);
}

void	ft_ls(char *path, int flag) 
{
	DIR *dir;
	t_dirent *dp;
	t_file *files;
	t_file *folders;
	
	if ((files = (t_file *)malloc(sizeof(t_file))) == NULL)
		return ;
	files = NULL;
	folders = NULL;
	if (open_dir(path, &dir))
	{
		while (read_dir(dir, &dp))
		{
			if (!(flag & f_seedots))
			{
				if (dp->d_name[0] != '.')
					storage_into_ll(dp, &files, &folders, path);
			}
			else
				storage_with_dots(dp, &files, &folders, path);
		}
		s_byflags(&files, &folders, flag);
		free_memory(&folders, &files, &dp);
		closedir(dir);
	}
	else
		error_msg(path);
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
			error_msg(argv[start]);
		else
			files[i++] = ft_strdup(argv[start]);
		start++;
	}
	Mergesort(files, 0, i - 1);
	files[i] = 0;
	if (i == 0)
		exit(DANGER);
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
		while (i <= argc - 1 && argv[i][0] == '-' && ft_strlen(argv[i]) > 1)
			parse_op_1(++argv[i++], &flag);
		if (i <= argc - 1)
		{
			if (!(argc - 1 - i >= 1))
				ft_ls(argv[i++], flag);
			else
			{
				files = test_file_exist(argv, argc, i);
				i = 0;
				while (files[i])
				{	
					ft_printf("%s:\n", files[i]);
					ft_ls(files[i], flag);
					if (files[i + 1] != NULL)
						ft_printf("\n");
					i++;
				}
			}
		}
		else	
			ft_ls(".", flag);
	}else
		ft_ls(".", flag);
	exit(SUCCESS);
}
