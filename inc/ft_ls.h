/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:05:10 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/08 15:36:24 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
# include <pwd.h>
# include <string.h>
# include <grp.h>
# include <time.h>
# include <unistd.h>

# define SUCCESS 0
# define FAILURE 1
# define DANGER 2

typedef struct dirent	t_dirent;

enum	e_flags
{
	f_flags = 1,
	f_xatt = 2,
	f_one = 4,
	f_seedots = 8,
	f_list = 16,
	f_recu = 32,
	f_rev = 64,
	f_time_m = 128
};

typedef struct 		s_stat
{
	time_t	smtime;
}					t_stat;

typedef struct		s_file
{
	t_dirent		*f_dp;
	int				flags;
	struct s_stat	f_stat;
	char			*path;
	struct s_file	*next;
	struct s_file	*prev;
}					t_file;

int					ft_strcmp(char *s1, char *s2);
size_t				ft_strlen(const char *str);
t_file				*ft_listnew(void);
char				*ft_stralloc(char *str, size_t len);
void				ft_putendl_fd(char const *str, int fd);
void				ft_putstr_fd(char const *str, int fd);
void				ft_putcharl_fd(char c, int fd);
void				mergeSort(t_file **source, int flag);
void				ft_push(struct s_file **head_ref, t_dirent *dp, t_stat stat, char *path);
char				*ft_strjoin(const char *s1, const char *s2);
int					ft_ls(char *path, int flag);
char				*ft_strdup(const char *src);
int					ft_timecmp(time_t f1, time_t f2);

#endif
