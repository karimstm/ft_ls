/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 09:54:57 by amoutik           #+#    #+#             */
/*   Updated: 2018/11/09 17:22:49 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			integer_handling(t_type *types, const char **format,
				char **str, va_list args)
{
	types->is_lower = 0;
	types->base = 10;
	if (**format == 'd' || **format == 'i')
	{
		types->flags |= SIGN;
		flags_conver_d(types, str, args);
		return (1);
	}
	else if (**format == 'D')
	{
		*str = ft_base_converter(*str, (ULONG)va_arg(args, ULONG), 10, *types);
		return (1);
	}
	else if (**format == 'u')
	{
		flags_conver_u(types, str, args);
		return (1);
	}
	else if (**format == 'U')
	{
		*str = ft_base_converter(*str, va_arg(args, ULONG), 10, *types);
		return (1);
	}
	return (0);
}

int			handling_oct_hex(t_type *types,
		const char **format, char **string, va_list args)
{
	types->is_lower = 1;
	types->base = 16;
	if (**format == 'o')
	{
		types->base = 8;
		flags_conver_o(types, string, args);
		return (1);
	}
	else if (**format == 'O')
	{
		*string = ft_base_converter(*string,
				va_arg(args, unsigned long int), 8, *types);
		return (1);
	}
	else if (flags_pointers(types, format, string, args))
		return (1);
	return (0);
}

int			spec_char(t_type *types, const char **format,
				char **string, va_list args)
{
	int i;

	i = 0;
	if (**format == 'c' || **format == '%')
	{
		if ((types->flags & LEFT) == 0)
			while (--types->width > 0)
			{
				*(*string)++ = ' ';
				ft_putchar(' ');
			}
		if (types->length.l)
		{
			i = ft_putwchar((wchar_t)va_arg(args, int));
			while (i-- > 0)
				*(*string)++ = ' ';
		}
		else
			ft_putchar(*(*string)++ = (**format == 'c') ? \
					(unsigned char)va_arg(args, int) : '%');
		while (--types->width > 0)
			ft_putchar(*(*string)++ = ' ');
		return (1);
	}
	return (0);
}

int			handling_char(t_type *types,
				const char **format, char **string, va_list args)
{
	int i;

	i = 0;
	if (spec_char(types, format, string, args))
		return (1);
	else if (**format == 'C')
	{
		if ((types->flags & LEFT) == 0)
			while (--types->width > 0)
			{
				*(*string)++ = ' ';
				ft_putchar(' ');
			}
		i = ft_putwchar(va_arg(args, wchar_t));
		while (i-- > 0)
			*(*string)++ = ' ';
		while (--types->width > 0)
		{
			*(*string)++ = ' ';
			ft_putchar(' ');
		}
		return (1);
	}
	return (0);
}

void		wide_string(t_type *types, char **string, va_list args)
{
	wchar_t		*wide;
	char		*nu;
	int			len;
	int			i;
	int			j;

	len = 0;
	i = 0;
	j = 0;
	nu = "(null)";
	wide = (wchar_t *)va_arg(args, wchar_t *);
	len = (wide) ? ft_wcnslen(wide, types->precision) \
		: ft_strnlen(nu, types->precision);
	if ((types->flags & LEFT) == 0)
		while (len < types->width--)
			ft_putchar(*(*string)++ = ' ');
	while (i++ < len)
		j += ft_putwchar((wide == NULL) ? *nu++ : *wide++);
	while (i++ < len)
		j += ft_putwchar(*nu++);
	while (j-- > 0)
		*(*string)++ = ' ';
	while (len < types->width--)
		ft_putchar(*(*string)++ = ' ');
}
