/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_listnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 14:59:27 by amoutik           #+#    #+#             */
/*   Updated: 2018/12/05 15:29:13 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_file	*ft_listnew(void)
{
	t_file *list;

	if (!(list = (t_file *)malloc(sizeof(t_file) * 1)))
		return (NULL);
	return (list);
}
