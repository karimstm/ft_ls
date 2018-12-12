/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:02:00 by amoutik           #+#    #+#             */
/*   Updated: 2018/11/08 18:27:52 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			do_div(long long *n, int base)
{
	int res;

	res = (unsigned long)(*n) % (unsigned)(base);
	*n = (unsigned long)(*n) / (unsigned)(base);
	return (res);
}

char		*ft_base_converter(char *str, long long nbr, int base, t_type typ)
{
	char	sign;
	char	*result;
	char	*buffer;
	int		i;
	int		num;

	num = -1;
	i = 0;
	typ.base = base;
	if (nbr == 0)
		num = 0;
	sign = 0;
	buffer = str;
	if (typ.precision != -1)
		typ.flags &= ~ZEROPAD;
	if ((result = (char *)malloc(sizeof(char) * 64)) == NULL)
		return (NULL);
	if (!ft_change_sign(&nbr, &sign, &typ))
		return (NULL);
	value_to_str(&i, &nbr, &typ, &result);
	set_width(&sign, &i, &str, &typ);
	force_pound_sign(&num, &str, &typ);
	print_result(&i, &str, &typ, &result);
	ft_putstr(buffer);
	return (str);
}
