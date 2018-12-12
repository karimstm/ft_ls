/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 11:12:25 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/12 16:28:33 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	user_perm(mode_t mode, char **p)
{
	int	res;

	if (mode & S_IRUSR)
		*(*p)++ = 'r';
	else
		*(*p)++ = '-';
	if (mode & S_IWUSR)
		*(*p)++ = 'w';
	else
		*(*p)++ = '-';
	res = mode & (S_IXUSR | S_ISUID);
	if (res == 0)
		*(*p)++ = '-';
	else if (res == S_IXUSR)
		*(*p)++ = 'x';
	else if (res ==  S_ISUID)
		*(*p)++ = 'S';
	else if (res == (S_IXUSR | S_ISUID))
		*(*p)++ = 's';
}

void	group_perm(mode_t mode, char **p)
{
	int res;

	if (mode & S_IRGRP)
		*(*p)++ = 'r';
	else
		*(*p)++ = '-';
	if (mode & S_IWGRP)
		*(*p)++ = 'w';
	else
		*(*p)++ = '-';
	res = mode & (S_IXGRP | S_ISGID);
	if (res == 0)
		*(*p)++ = '-';
	else if (res == S_IXGRP)
		*(*p)++ = 'x';
	else if (res ==  S_ISGID)
		*(*p)++ = 'S';
	else if (res == (S_IXGRP | S_ISGID))
		*(*p)++ = 's';
}

void	other_perm(mode_t mode, char **p)
{
	int res;

	if (mode & S_IROTH)
		*(*p)++ = 'r';
	else
		*(*p)++ = '-';
	if (mode & S_IWOTH)
		*(*p)++ = 'w';
	else
		*(*p)++ = '-';
	res = mode & (S_IXOTH | S_ISVTX);
	if (res == 0)
		*(*p)++ = '-';
	else if (res == S_IXOTH)
		*(*p)++ = 'x';
	else if (res ==  S_ISVTX)
		*(*p)++ = 'T';
	else if (res == (S_IXOTH | S_ISVTX))
		*(*p)++ = 't';
}

void	acl_perm(char **p, char *filename)
{
	acl_t acl = NULL;
	acl_entry_t dummy;
	ssize_t xattr = 0;

	acl = acl_get_link_np(filename, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1) {
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(filename, NULL, 0, XATTR_NOFOLLOW);
	if (xattr < 0)
		xattr = 0;

	if (xattr > 0)
		*(*p)++ = '@';
	else if (acl != NULL)
		*(*p)++ = '+';
	else
		*(*p)++ = ' ';
	*(*p) = '\0';
}

void	ft_strmode(mode_t mode, char *p, char *path)
{
	if (M_ISREG(mode))
		*p++ = '-';
	else if (M_ISBLK(mode))
		*p++ = 'b';
	else if (M_ISCHR(mode))
		*p++ = 'c';
	else if (M_ISDIR(mode))
		*p++ = 'd';
	else if (M_ISLNK(mode))
		*p++ = 'l';
	else if (M_ISFIFO(mode))
		*p++ = 'p';
	else if (M_ISSOCK(mode))
		*p++ = 's';
	else if(M_ISWHT(mode))
		*p++ = 'w';
	else
		*p++ = '?';
	user_perm(mode, &p);
	group_perm(mode, &p);
	other_perm(mode, &p);
	acl_perm(&p, path);
}
