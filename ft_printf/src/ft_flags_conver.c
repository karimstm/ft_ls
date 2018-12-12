/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_conver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:15:00 by amoutik           #+#    #+#             */
/*   Updated: 2018/11/09 11:25:09 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		flags_conver_d(t_type *types,
		char **string, va_list args)
{
	if (types->length.hh == 1)
		*string = ft_base_converter(*string,
			(signed char)va_arg(args, unsigned int), 10, *types);
	else if (types->length.ll == 1)
		*string = ft_base_converter(*string,
			va_arg(args, long long), 10, *types);
	else if (types->length.l == 1)
		*string = ft_base_converter(*string,
			va_arg(args, long int), 10, *types);
	else if (types->length.j == 1)
		*string = ft_base_converter(*string,
			(intmax_t)va_arg(args, intmax_t), 10, *types);
	else if (types->length.h == 1)
		*string = ft_base_converter(*string,
			(short int)va_arg(args, int), 10, *types);
	else if (types->length.z == 1)
		*string = ft_base_converter(*string,
			(size_t)va_arg(args, size_t), 10, *types);
	else if (types->length.t)
		*string = ft_base_converter(*string,
			(ptrdiff_t)va_arg(args, ptrdiff_t), 10, *types);
	else
		*string = ft_base_converter(*string, va_arg(args, int), 10, *types);
}

void		flags_conver_u(t_type *types, char **string, va_list args)
{
	if (types->length.hh)
		*string = ft_base_converter(*string,
				(unsigned char)va_arg(args, int), 10, *types);
	else if (types->length.ll)
		*string = ft_base_converter(*string,
				va_arg(args, unsigned long long int), 10, *types);
	else if (types->length.h)
		*string = ft_base_converter(*string,
				(unsigned short int)va_arg(args, unsigned int), 10, *types);
	else if (types->length.l)
		*string = ft_base_converter(*string,
			va_arg(args, unsigned long int), 10, *types);
	else if (types->length.j)
		*string = ft_base_converter(*string,
			va_arg(args, uintmax_t), 10, *types);
	else if (types->length.z)
		*string = ft_base_converter(*string,
			va_arg(args, size_t), 10, *types);
	else if (types->length.t)
		*string = ft_base_converter(*string,
			(ptrdiff_t)va_arg(args, ptrdiff_t), 10, *types);
	else
		*string = ft_base_converter(*string,
				va_arg(args, unsigned int), 10, *types);
}

void		flags_conver_o(t_type *types, char **string, va_list args)
{
	if (types->length.hh)
		*string = ft_base_converter(*string,
				(unsigned char)va_arg(args, int), 8, *types);
	else if (types->length.ll)
		*string = ft_base_converter(*string,
				va_arg(args, unsigned long long int), 8, *types);
	else if (types->length.h)
		*string = ft_base_converter(*string,
				(unsigned short int)va_arg(args, unsigned int), 8, *types);
	else if (types->length.l)
		*string = ft_base_converter(*string,
				va_arg(args, unsigned long int), 8, *types);
	else if (types->length.j)
		*string = ft_base_converter(*string,
				va_arg(args, uintmax_t), 8, *types);
	else if (types->length.z)
		*string = ft_base_converter(*string,
				va_arg(args, size_t), 8, *types);
	else if (types->length.t)
		*string = ft_base_converter(*string,
				(ptrdiff_t)va_arg(args, ptrdiff_t), 8, *types);
	else
		*string = ft_base_converter(*string,
				(unsigned int)va_arg(args, int), 8, *types);
}

void		flags_conver_x(t_type *types, char **string, va_list args)
{
	if (types->length.hh)
		*string = ft_base_converter(*string,
			(unsigned char)va_arg(args, int), 16, *types);
	else if (types->length.ll)
		*string = ft_base_converter(*string,
				va_arg(args, unsigned long long int), 16, *types);
	else if (types->length.h)
		*string = ft_base_converter(*string,
				(unsigned short int)va_arg(args, unsigned int), 16, *types);
	else if (types->length.l)
		*string = ft_base_converter(*string,
			va_arg(args, unsigned long int), 16, *types);
	else if (types->length.j)
		*string = ft_base_converter(*string,
			va_arg(args, uintmax_t), 16, *types);
	else if (types->length.z)
		*string = ft_base_converter(*string,
			va_arg(args, size_t), 16, *types);
	else if (types->length.t)
		*string = ft_base_converter(*string,
			(ptrdiff_t)va_arg(args, ptrdiff_t), 16, *types);
	else
		*string = ft_base_converter(*string,
			va_arg(args, unsigned int), 16, *types);
}

int			flags_pointers(t_type *types,
		const char **format, char **string, va_list args)
{
	if (**format == 'x')
	{
		flags_conver_x(types, string, args);
		return (1);
	}
	else if (**format == 'X')
	{
		types->is_lower = 0;
		flags_conver_x(types, string, args);
		return (1);
	}
	else if (**format == 'p')
	{
		types->is_pointer = 'p';
		types->flags |= SPECIAL;
		if (types->width == -1)
			types->flags |= ZEROPAD;
		*string = ft_base_converter(*string,
			(uintptr_t)va_arg(args, void *), 16, *types);
		return (1);
	}
	return (0);
}
