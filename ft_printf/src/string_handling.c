/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:51:28 by amoutik           #+#    #+#             */
/*   Updated: 2018/11/09 16:53:50 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		normal_string(t_type *types, char **string, va_list args)
{
	char	*at;
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (types->length.l != 1)
	{
		if ((at = va_arg(args, char *)) == NULL)
			at = ft_strdup("(null)");
		len = ft_strnlen(at, types->precision);
		if ((types->flags & LEFT) == 0)
			while (len < types->width--)
				ft_putchar(*(*string)++ = ' ');
		while (i++ < len)
			ft_putchar(*(*string)++ = (unsigned int)*at++);
		while (len < types->width--)
			ft_putchar(*(*string)++ = ' ');
	}
	else
		wide_string(types, string, args);
}

int			handling_string(t_type *types, const char **format,
		char **string, va_list args)
{
	if (**format == 's')
	{
		normal_string(types, string, args);
		return (1);
	}
	if (**format == 'S')
	{
		wide_string(types, string, args);
		return (1);
	}
	return (0);
}

int			handling_n(char **buf, t_length *length,
		char **string, va_list args)
{
	long *n;

	if (length->l == 1)
		n = va_arg(args, long *);
	else if (length->hh)
		n = (long *)va_arg(args, signed char *);
	else if (length->h)
		n = (long *)va_arg(args, short int *);
	else if (length->ll)
		n = (long *)va_arg(args, long long int *);
	else if (length->l)
		n = (long *)va_arg(args, long int *);
	else if (length->j)
		n = (long *)va_arg(args, intmax_t *);
	else if (length->z)
		n = (long *)va_arg(args, size_t *);
	else if (length->t)
		n = (long *)va_arg(args, ptrdiff_t *);
	else
		n = (long *)va_arg(args, int *);
	*n = (*string - (*buf));
	return (1);
}
