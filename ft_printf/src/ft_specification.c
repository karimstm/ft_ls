/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specification.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:29:43 by amoutik           #+#    #+#             */
/*   Updated: 2018/11/08 18:30:18 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		flags_handling(t_type *type, const char **format)
{
	type->flags = 0;
	while (1)
	{
		if ((**format) == '-')
			(*type).flags |= LEFT;
		else if ((**format) == '+')
			(*type).flags |= PLUS;
		else if ((**format) == ' ')
			(*type).flags |= SPACE;
		else if ((**format) == '#')
			(*type).flags |= SPECIAL;
		else if ((**format) == '0')
			(*type).flags |= ZEROPAD;
		else
			break ;
		++(*format);
	}
}

void		fields_handling(t_type *type, const char **format, va_list args)
{
	type->width = -1;
	if (**format == '*')
	{
		++(*format);
		type->width = va_arg(args, int);
		if (type->width < 0)
		{
			type->width = -type->width;
			type->flags |= LEFT;
		}
	}
	if (ft_isdigit(**format))
		type->width = ft_atoi(format);
}

void		precision_handling(t_type *types, const char **format, va_list args)
{
	types->precision = -1;
	types->has_prec = 0;
	if (**format == '.')
	{
		types->has_prec = 1;
		++(*format);
		if (ft_isdigit(**format))
			types->precision = ft_atoi(format);
		else if (**format == '*')
		{
			++(*format);
			types->precision = va_arg(args, int);
		}
	}
}

void		lenght_handling(t_length *len, const char **format)
{
	if ((*format)[0] == 'h' && (*format)[1] == 'h' && (len->hh = 1))
		(*format) += 2;
	else if ((*format)[0] == 'l' && (*format)[1] == 'l' && (len->ll = 1))
		(*format) += 2;
	else if (**format == 'h' && (len->h = 1))
		(*format)++;
	else if (**format == 'l' && (len->l = 1))
		(*format)++;
	else if (**format == 'j' && (len->j = 1))
		(*format)++;
	else if (**format == 'z' && (len->z = 1))
		(*format)++;
	else if (**format == 't' && (len->t = 1))
		(*format)++;
}
