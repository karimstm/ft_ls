/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 10:54:10 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/12 11:02:15 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	error_msg(char *path)
{
	int 		error;
	struct stat	buf;

	error = lstat(path, &buf);
	if (error == -1)
	{
		ft_putstr_fd(ft_strjoin("ft_ls: ", path), 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else
	{
		ft_putstr_fd(ft_strjoin("ft_ls: ", path), 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}	
}
