/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amoutik <abdelkarimoutik@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 10:07:11 by amoutik           #+#    #+#             */
/*   Updated: 2018/11/09 17:03:07 by amoutik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>
# include <string.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <wchar.h>
# include <locale.h>
# include <stddef.h>
# include <unistd.h>

# define ZEROPAD 0x01
# define SIGN    0x02
# define PLUS    0x04
# define SPACE   0x08
# define LEFT    0x10
# define SMALL   0x20
# define SPECIAL 0x40
# define ULONG unsigned long

typedef struct	s_length
{
	int hh;
	int ll;
	int h;
	int l;
	int j;
	int z;
	int t;
}				t_length;

typedef struct	s_type
{
	int			width;
	int			precision;
	int			flags;
	int			is_lower;
	int			lenght;
	int			has_prec;
	int			base;
	char		is_pointer;
	t_length	length;
}				t_type;

int				ft_printf(const char *format, ...);
void			ft_putchar(char c);
void			ft_putnbr(int nb);
int				ft_isdigit(int c);
int				ft_atoi(const char **s);
size_t			ft_strnlen(const char *s, size_t maxlen);
char			*ft_base_converter(char *string,
					long long nbr, int base, t_type types);
size_t			ft_wcslen (const wchar_t *s);
int				ft_putwchar(wchar_t c);
void			ft_putwstr(int *str);
size_t			ft_wcnslen(const wchar_t *s, size_t maxlen);
size_t			ft_strlen(const char *s);
char			*ft_reverse(const char *s);
void			ft_putstr(const char *s);
void			ft_putnwstr(const wchar_t *str, size_t len);
void			flags_conver_d(t_type *types, char **string, va_list args);
void			flags_conver_u(t_type *types, char **string, va_list args);
void			flags_conver_o(t_type *types, char **string, va_list args);
void			flags_conver_x(t_type *types, char **string, va_list args);
int				flags_pointers(t_type *types,
					const char **format, char **string, va_list args);
char			*ft_strdup(const char *s);
int				ft_change_sign(long long *nbr, char *sign, t_type *types);
void			set_width(char *sign, int *i, char **string, t_type *types);
void			force_pound_sign(int *num, char **string,
							t_type *types);
void			print_result(int *i, char **string,
							t_type *types, char **result);
void			value_to_str(int *i, long long *nbr,
							t_type *types, char **result);
int				do_div(long long *n, int base);
int				integer_handling(t_type *types,
							const char **format, char **string, va_list args);
int				handling_oct_hex(t_type *types,
					const char **format, char **string, va_list args);
int				spec_char(t_type *types,
					const char **format, char **string, va_list args);
int				handling_char(t_type *types,
					const char **format, char **string, va_list args);
void			wide_string(t_type *types, char **string, va_list args);
void			flags_handling(t_type *type, const char **format);
void			precision_handling(t_type *types,
					const char **format, va_list args);
void			lenght_handling(t_length *len,
					const char **format);
void			fields_handling(t_type *type,
					const char **format, va_list args);
int				handling_n(char **buf, t_length *length,
				char **string, va_list args);
int				handling_string(t_type *types, const char **format,
				char **string, va_list args);
void			normal_string(t_type *types, char **string, va_list args);
#endif
