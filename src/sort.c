/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 11:25:18 by mfilahi           #+#    #+#             */
/*   Updated: 2018/12/13 14:56:23 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	merge(char **a, int low, int mid, int high)
{
	char	**b;
	int		i;
	int		j;
	int		k;

	b = (char **)malloc(sizeof(char *) * (high - low + 1));
	i = low;
	j = mid + 1;
	k = 0;
	while (i <= mid && j <= high)
		if (ft_strcmp(a[i], a[j]))
			b[k++] = ft_strdup(a[i++]);
		else
			b[k++] = ft_strdup(a[j++]);
	while (i <= mid)
		b[k++] = ft_strdup(a[i++]);
	while (j <= high)
		b[k++] = ft_strdup(a[j++]);
	k--;
	while (k >= 0)
	{
		a[low + k] = ft_strdup(b[k]);
		k--;
	}
}

void	merge_sort(char **a, int low, int high)
{
	int m;

	if (low < high)
	{
		m = (high + low) / 2;
		merge_sort(a, low, m);
		merge_sort(a, m + 1, high);
		merge(a, low, m, high);
	}
}
