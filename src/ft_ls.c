/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:20:32 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/13 14:55:20 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void		storage_into_ll(t_dirent *dp, t_file **files,
		t_file **folders, char *path)
{
	char		*tmp;
	struct stat	buf;
	t_stat		mystat;
	char		*newpath;

	newpath = ft_strjoin(path, "/");
	lstat(ft_strjoin(newpath, dp->d_name), &buf);
	mystat.smtime = buf.st_mtime;
	ft_push(&(*files), dp, mystat, ft_strjoin(newpath, dp->d_name));
	get_len(&g_lenstat, buf);
	if (dp->d_type == DT_DIR)
	{
		tmp = ft_strjoin(path, "/");
		tmp = ft_strjoin(tmp, dp->d_name);
		ft_push(&(*folders), dp, mystat, tmp);
		free(tmp);
	}
	free(newpath);
}

void		storage_with_dots(t_dirent *dp, t_file **files,
		t_file **folders, char *path)
{
	char		*tmp;
	struct stat	buf;
	t_stat		mystat;
	char		*newpath;

	newpath = ft_strjoin(path, "/");
	lstat(ft_strjoin(newpath, dp->d_name), &buf);
	mystat.smtime = buf.st_mtime;
	if (buf.st_mode == 0)
		return ;
	ft_push(&(*files), dp, mystat, ft_strjoin(newpath, dp->d_name));
	get_len(&g_lenstat, buf);
	if (dp->d_type == DT_DIR && !(ft_strcmp(dp->d_name, ".") == 0
				|| ft_strcmp(dp->d_name, "..") == 0))
	{
		tmp = ft_strjoin(path, "/");
		tmp = ft_strjoin(tmp, dp->d_name);
		ft_push(&(*folders), dp, mystat, tmp);
		free(tmp);
	}
	free(newpath);
}

void		s_byflags(t_file **files, t_file **folders, int flag)
{
	if (!(flag & f_no_sort))
		g_merge_sort(&(*files), flag);
	print_total(flag);
	if (flag & f_recu)
	{
		print_files(*files, flag);
		if (!(flag & f_no_sort))
			g_merge_sort(&(*folders), flag);
		print_folders(*folders, flag);
	}
	else
		print_files(*files, flag);
}

void		s_ft_ls(t_dirent *dp, t_file **files, t_file **folders, char *path)
{
	if (dp->d_name[0] != '.')
		storage_into_ll(dp, files, folders, path);
}

void		ft_ls(char *path, int flag)
{
	DIR			*dir;
	t_dirent	*dp;
	t_file		*files;
	t_file		*folders;

	if ((files = (t_file *)malloc(sizeof(t_file))) == NULL)
		return ;
	files = NULL;
	folders = NULL;
	if (open_dir(path, &dir))
	{
		while (read_dir(dir, &dp))
		{
			if (!(flag & f_seedots))
				s_ft_ls(dp, &files, &folders, path);
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
