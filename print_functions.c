/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:07:09 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/25 14:05:15 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill(t_flag *flag, va_list ap)
{
	fill_specifier(flag);
	if (ft_strlen(flag->str) > 1)
	{
		fill_flags(flag);
		fill_width(flag, ap);
		fill_len_mod(flag, 'h');
		fill_len_mod(flag, 'l');
		fill_len_mod(flag, 'L');
	}
	if (ft_strlen(flag->str) > 1)
		fill_precision(flag, ap);
}

int	put_format(t_flag *flag, va_list ap)
{
	fill(flag, ap);
	if (flag->spec == 'c')
		return (print_c(flag, ap));
	else if (flag->spec == 's')
		return (print_s(flag, ap));
	else if (flag->spec == 'd' || flag->spec == 'i')
		return (print_signed_int(flag, ap));
	else if (is_char_in_str(flag->spec, UINT) == TRUE)
		return (print_unsigned_int(flag, ap));
	else if (flag->spec == 'f')
		return (print_float(flag, ap));
	else if (flag->spec == '%')
		return (handle_char(flag, '%'));
	return (0);
}

int	handle_char(t_flag *flag, char c)
{
	if (flag->width < 1)
		return (write(1, &c, 1));
	if (flag->dash == TRUE)
		return (write(1, &c, 1) + putchar_nbyte(' ', flag->width - 1));
	if (flag->zero == TRUE)
		return (putchar_nbyte('0', flag->width - 1) + write(1, &c, 1));
	return (putchar_nbyte(' ', flag->width - 1) + write(1, &c, 1));
}

int	print_c(t_flag *flag, va_list ap)
{
	char	c;

	c = va_arg(ap, int);
	return (handle_char(flag, c));
}

int	print_s(t_flag *flag, va_list ap)
{
	char	*s;
	int		len;

	s = va_arg(ap, char *);
	if (s == NULL)
		s = "(null)";
	len = ft_strlen(s);
	if (flag->dot == TRUE && flag->prec >= 0 && flag->prec < len)
		len = flag->prec;
	if (flag->width <= len)
		return (putstr_nbyte(s, len));
	if (flag->dash == TRUE)
		return (putstr_nbyte(s, len) + putchar_nbyte(' ', flag->width - len));
	return (putchar_nbyte(' ', flag->width - len) + putstr_nbyte(s, len));
}
