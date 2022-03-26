/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:07:09 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/26 21:37:48 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int	print_char(t_flag *flag, va_list ap)
{
	char	c;

	c = va_arg(ap, int);
	return (handle_char(flag, c));
}

int	print_str(t_flag *flag, va_list ap)
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
