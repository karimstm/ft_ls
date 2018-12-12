/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_converter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:46:45 by amoutik           #+#    #+#             */
/*   Updated: 2018/11/08 18:28:14 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

int			ft_change_sign(long long *nbr, char *sign, t_type *types)
{
	if (types->base < 2 || types->base > 16)
		return (0);
	if (types->flags & SIGN)
	{
		if (*nbr < 0)
		{
			*sign = '-';
			*nbr = -*nbr;
			types->width--;
		}
		else if (types->flags & PLUS)
		{
			*sign = '+';
			types->width--;
		}
		else if (types->flags & SPACE)
		{
			*sign = ' ';
			types->width--;
		}
	}
	return (1);
}

void		set_width(char *sign, int *i, char **string, t_type *types)
{
	if (types->flags & SPECIAL)
	{
		if (types->base == 16)
			types->width -= 2;
		else if (types->base == 8)
			types->width--;
	}
	if (*i > types->precision)
		types->precision = *i;
	types->width -= types->precision;
	if (!(types->flags & (ZEROPAD | LEFT)))
		while (types->width-- > 0)
			*(*string)++ = ' ';
	if (*sign)
		*(*string)++ = *sign;
}

void		force_pound_sign(int *num, char **string, t_type *types)
{
	if (types->flags & SPECIAL)
	{
		if (types->base == 8 && (*num != 0 || types->has_prec))
			*(*string)++ = '0';
		else if (types->base == 16 && (*num != 0 || types->is_pointer == 'p'))
		{
			*(*string)++ = '0';
			*(*string)++ = (types->is_lower ? 'x' : 'X');
		}
		else if (types->base == 16 && *num != 0)
		{
			*(*string)++ = '0';
			*(*string)++ = (types->is_lower ? 'x' : 'X');
		}
	}
}

void		print_result(int *i, char **string, t_type *types, char **result)
{
	if (!(types->flags & LEFT))
		while (types->width-- > 0)
			*(*string)++ = (types->flags & ZEROPAD) ? '0' : ' ';
	while (*i < types->precision--)
		*(*string)++ = '0';
	while ((*i)-- > 0)
		*(*string)++ = (*result)[*i];
	while (types->width-- > 0)
		*(*string)++ = ' ';
	*(*string) = '\0';
}

void		value_to_str(int *i, long long *nbr, t_type *types, char **result)
{
	const char digitsupper[16] = "0123456789ABCDEF";
	const char digitslower[16] = "0123456789abcdef";

	if (!types->has_prec && *nbr == 0)
		(*result)[(*i)++] = '0';
	else
	{
		while (*nbr != 0)
		{
			if (types->is_lower)
				(*result)[(*i)++] = digitslower[do_div(nbr, types->base)];
			else
				(*result)[(*i)++] = digitsupper[do_div(nbr, types->base)];
		}
	}
}
