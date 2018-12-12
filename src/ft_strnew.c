/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 14:32:21 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/11 14:33:06 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

char	*ft_strnew(size_t size)
{
	char		*string;
	size_t		i;

	if ((string = (char *)malloc(size + 1)) == NULL)
		return (NULL);
	i = 0;
	while (i <= size + 1)
		string[i++] = '\0';
	return (string);
}
