/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 14:25:47 by mfilahi           #+#    #+#             */
/*   Updated: 2018/12/13 14:48:40 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_total(int flag)
{
	if (flag & f_list)
		ft_printf("total %lld\n", g_lenstat.total_block);
}

void		print_list(t_file *list_files, int flag, struct stat *sb)
{
	if (flag & f_rev)
	{
		print_files(list_files->next, flag);
		g_lenstat.total_block = 0;
	}
	lstat(list_files->path, sb);
	if (flag & f_blocksz)
		ft_printf("%*d ", g_lenstat.blocksize, sb->st_blocks);
	get_permissions(sb->st_mode, list_files->path);
	ft_printf("%*d ", g_lenstat.hardlen, sb->st_nlink);
	if (!(flag & f_no_owner))
		ft_printf("%-*s  ", (int)g_lenstat.userlen,
				(getpwuid(sb->st_uid))->pw_name);
	if (!(flag & f_no_group))
		ft_printf("%-*s  ", (int)g_lenstat.grouplen,
				(getgrgid(sb->st_gid))->gr_name);
	ft_printf("%*lld ", g_lenstat.sizelen, sb->st_size);
	ft_printf("%s ", ft_strtrim(ctime(&sb->st_mtimespec.tv_sec)));
}

void		print_files(t_file *list_files, int flag)
{
	struct stat	sb;

	if (list_files)
	{
		if (flag & f_list)
			print_list(list_files, flag, &sb);
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
	g_lenstat.total_block = 0;
}

void		print_folders(t_file *folders, int flag)
{
	if (folders)
	{
		if (flag & f_rev)
			print_folders(folders->next, flag);
		ft_printf("\n%s:\n", folders->path);
		ft_ls(folders->path, flag);
		if (!(flag & f_rev))
			print_folders(folders->next, flag);
		init_stat(&g_lenstat);
	}
}

void		get_len(t_stat *stat, struct stat sb)
{
	stat->hardlen = MAX(stat->hardlen, number_len(sb.st_nlink));
	stat->userlen = MAX(stat->userlen,
			ft_strlen((getpwuid(sb.st_uid))->pw_name));
	stat->grouplen = MAX(stat->grouplen,
			ft_strlen((getgrgid(sb.st_gid))->gr_name));
	stat->blocksize = MAX(stat->blocksize, number_len(sb.st_blocks));
	stat->sizelen = MAX(stat->sizelen, number_len(sb.st_size));
	stat->total_block += sb.st_blocks;
}
