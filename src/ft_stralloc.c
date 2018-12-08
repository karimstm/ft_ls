/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stralloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 15:13:09 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/08 09:33:59 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

char	*ft_stralloc(char *src, size_t len)
{
	char	*string;
	int		i;

	if ((string = (char *)malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	i = 0;
	while (*src)
		string[i++] = *src++;
	string[i] = '\0';
	return (string);
}
