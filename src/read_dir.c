/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 14:20:26 by mfilahi           #+#    #+#             */
/*   Updated: 2018/12/13 14:21:59 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			open_dir(char *path, DIR **dir)
{
	if ((*dir = opendir(path)) != NULL)
		return (1);
	return (0);
}

int			read_dir(DIR *dir, t_dirent **dp)
{
	if ((*dp = readdir(dir)) != NULL)
		return (1);
	return (0);
}

void		init_stat(t_stat *stat)
{
	stat->hardlen = 0;
	stat->userlen = 0;
	stat->grouplen = 0;
	stat->sizelen = 0;
	stat->blocksize = 0;
}

void		linkname(off_t st_size, char *path)
{
	char *linkname;

	linkname = malloc(st_size + 1);
	if (linkname == NULL)
		return ;
	if (readlink(path, linkname, st_size + 1))
		ft_printf(" -> %s", linkname);
	free(linkname);
}

void		get_permissions(mode_t st_mode, char *path)
{
	char perm[20];

	ft_strmode(st_mode, perm, path);
	ft_printf("%s ", perm);
}
