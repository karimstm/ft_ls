/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getxattr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 14:20:23 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/12 16:27:38 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	ft_getxattr(char *path)
{
	ssize_t	value;
	char	name[1024];
	size_t	len;
	ssize_t key;

	len = listxattr(path, name, 0, 0);
	key = listxattr(path, name, len, 0);
	if ((value = getxattr(path, name, NULL, 0, 0, 0)) > 0)
		printf("        %s      %zd\n", name, value);
}
