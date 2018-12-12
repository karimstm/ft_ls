/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:36:50 by amoutik           #+#    #+#             */
/*   Updated: 2018/11/08 16:37:42 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_reverse(const char *s)
{
	int		start;
	int		end;
	char	*string;

	start = 0;
	end = ft_strlen(s) - 1;
	string = (char *)s;
	while (start < end)
	{
		string[start] ^= string[end];
		string[end] ^= string[start];
		string[start] ^= string[end];
		++start;
		--end;
	}
	return (string);
}
