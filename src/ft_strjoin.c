/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 16:06:42 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/13 11:24:13 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*string;
	unsigned int	len_s1;
	unsigned int	len_s2;
	unsigned int	i;

	len_s1 = ft_strlen((char *)s1);
	len_s2 = ft_strlen((char *)s2);
	string = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (string == NULL)
		return (NULL);
	i = 0;
	while (*s1 && (string[i++] = *s1))
		s1++;
	while (*s2 && (string[i++] = *s2))
		s2++;
	string[i] = '\0';
	return (string);
}
