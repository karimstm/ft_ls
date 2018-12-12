/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:11:03 by amoutik           #+#    #+#             */
/*   Updated: 2018/11/10 08:19:59 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		len_initial(t_type *type)
{
	type->length.hh = 0;
	type->length.ll = 0;
	type->length.h = 0;
	type->length.l = 0;
	type->length.j = 0;
	type->length.z = 0;
	type->length.t = 0;
}

int			s_print(t_type *types, const char **format,
				char **string, va_list args)
{
	flags_handling(types, format);
	fields_handling(types, format, args);
	precision_handling(types, format, args);
	lenght_handling(&types->length, format);
	if (integer_handling(types, format, string, args))
	{
		(*format)++;
		return (1);
	}
	else if (handling_oct_hex(types, format, string, args))
	{
		(*format)++;
		return (1);
	}
	else if (handling_char(types, format, string, args))
	{
		(*format)++;
		return (1);
	}
	else if (handling_string(types, format, string, args))
	{
		(*format)++;
		return (1);
	}
	return (0);
}

void		addition_chars(const char **format, char **string)
{
	ft_putchar(*(*string) = *(*format));
	*(*format) ? (*string)++ : 0;
}

int			ft_vsprintf(char *buf, const char *format, va_list args)
{
	char	*string;
	t_type	types;

	string = buf;
	while (*format)
	{
		while (*format && *format != '%')
			ft_putchar(*string++ = *format++);
		if (*format == '%')
		{
			++format;
			len_initial(&types);
			if (s_print(&types, &format, &string, args))
				continue;
			else if (*format == 'n')
			{
				if (handling_n(&buf, &types.length, &string, args))
					continue;
			}
			else
				addition_chars(&format, &string);
		}
		(*format) ? format++ : 0;
	}
	return (string - buf);
}

int			ft_printf(const char *format, ...)
{
	char	buf[50000];
	va_list	args;
	int		ret;

	va_start(args, format);
	ret = ft_vsprintf(buf, format, args);
	va_end(args);
	return (ret);
}
