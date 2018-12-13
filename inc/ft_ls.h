/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:05:10 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/13 13:12:38 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <string.h>
# include <grp.h>
# include <time.h>
# include <unistd.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include "ft_printf.h"

# define SUCCESS 0
# define FAILURE 1
# define DANGER 2
# define MAX(a, b) ((a) >= (b) ? (a) : (b))
# define M__FIFO(m) ((m & 0170000) == 0140000)
# define M_ISDIR(m)	((m & 0170000) == 0040000)
# define M_ISCHR(m)	((m & 0170000) == 0020000)
# define M_ISBLK(m)	((m & 0170000) == 0060000)
# define M_ISREG(m)	((m & 0170000) == 0100000)
# define M_ISFIFO(m) (((m & 0170000) == 0010000) || M__FIFO(m))
# define M_ISLNK(m)	((m & 0170000) == 0120000)
# define M_ISSOCK(m) (((m & 0170000) == 0010000) || M__FIFO(m))
# define M_ISWHT(m)	((m & 0170000) == 0160000)

typedef struct dirent	t_dirent;
typedef long long int	t_llint;

enum	e_flags
{
	f_flags = 0x1,
	f_xatt = 0x2,
	f_one = 0x4,
	f_seedots = 0x8,
	f_list = 0x10,
	f_recu = 0x20,
	f_rev = 0x40,
	f_time_m = 0x80,
	f_no_owner = 0x100,
	f_no_group = 0x200,
	f_no_sort = 0x400,
	f_blocksz = 0x800
};

typedef struct		s_stat
{
	time_t	smtime;
	int		hardlen;
	size_t	userlen;
	size_t	grouplen;
	int		sizelen;
	int		blocksize;
	t_llint	total_block;
}					t_stat;

typedef struct		s_file
{
	t_dirent		*f_dp;
	int				flags;
	char			*d_name;
	int				user_id;
	int				group_id;
	struct s_stat	f_stat;
	char			*path;
	struct s_file	*next;
}					t_file;

int					ft_strcmp(char *s1, char *s2);
size_t				ft_strlen(const char *str);
t_file				*ft_listnew(void);
char				*ft_stralloc(char *str, size_t len);
void				ft_putendl_fd(char const *str, int fd);
void				ft_putstr_fd(char const *str, int fd);
void				ft_putcharl_fd(char c, int fd);
void				mergeSort(t_file **source, int flag);
void				ft_push(struct s_file **head_ref, t_dirent *dp,
							t_stat stat, char *path);
char				*ft_strjoin(const char *s1, const char *s2);
void				ft_ls(char *path, int flag);
char				*ft_strdup(const char *src);
int					ft_timecmp(time_t f1, time_t f2);
void				Mergesort(char **a, int low, int high);
int					number_len(long long int value);
int					ft_isspace(int c);
char				*ft_strtrim(char const *s);
char				*ft_strnew(size_t size);
void				error_msg(char *path);
void				ft_strmode(mode_t mode, char *p, char *path);
void				ft_getxattr(char *path);

#endif
