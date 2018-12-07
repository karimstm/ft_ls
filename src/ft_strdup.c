/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 16:36:57 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/07 17:42:49 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

char	*ft_strdup(const char *src)
{
	char	*string;
	int		i;

	i = 0;
	string = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (string == NULL)
		return (NULL);
	while (src[i])
	{
		string[i] = src[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}
