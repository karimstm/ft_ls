/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 14:28:43 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/12 16:28:57 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

char	*ft_strtrim(char const *s)
{
	char			*string;
	unsigned int	i;
	unsigned int	counter;
	unsigned int	len;
	unsigned int	j;

	i = 0;
	counter = 0;
	j = 0;
	len = ft_strlen((char *)s);
	while (s[i] && (ft_isspace(s[i]) || i < 4))
		i++;
	if (s[i] == '\0')
		return (ft_strnew(0));
	while (s[len - 1] && (ft_isspace(s[len - 1]) || j++ < 7))
		len--;
	if ((string = (char *)malloc(sizeof(char) * (len - i + 1))) == NULL)
		return (NULL);
	j = 0;
	while (s[i] && i < len)
	{
		string[j++] = s[i++];
	}
	string[j] = '\0';
	return (string);
}
