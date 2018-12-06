/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:05:10 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/06 09:20:39 by amoutik          ###   ########.fr       */
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

typedef struct		s_file
{
	char			*f_name;
	int				flags;
	struct s_file	*next;
	struct s_file	*prev;
}					t_file;

int					ft_strcmp(char *s1, char *s2);
size_t				ft_strlen(char *str);
t_file				*ft_listnew(void);
char				*ft_stralloc(char *str, size_t len);
void				ft_putendl_fd(char const *str, int fd);
void				ft_putstr_fd(char const *str, int fd);
void				ft_putcharl_fd(char c, int fd);
#endif
