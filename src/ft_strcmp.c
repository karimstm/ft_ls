/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:48:44 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/10 15:36:57 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int		ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (((unsigned char)*s1) - ((unsigned char)*s2) == 0)
		return (0);
	return (((unsigned char)*s1 - (unsigned char)*s2) < 0 ? -1 : 1);
}
