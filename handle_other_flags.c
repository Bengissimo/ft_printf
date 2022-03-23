/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_other_flags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:39:41 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/23 11:25:31 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	fill_char(t_flag *flag, int negative)
{
	if (negative == TRUE)
		return ('-');
	if (flag->plus == TRUE)
		return ('+');
	if (flag->space == TRUE)
		return (' ');
	return ('\0');
}
int	handle_plus_or_space(t_flag *flag, char *str, int negative)
{
	int			ret;
	uintmax_t	len;
	char		fill;
	int n_byte;

	fill = fill_char(flag, negative);
	if (fill == '\0')
		n_byte = 0;
	else
		n_byte = 1;
	ret = putchar_nbyte(fill, n_byte);
	len = ft_strlen(str);
	if (flag->hash == TRUE && flag->spec == 'o' && *str != '0')
		ret += write(1, "0", 1);
	if (flag->hash == TRUE && flag->spec == 'x' && *str != '0')
		ret += write(1, "0x", 2);
	if (flag->hash == TRUE && flag->spec == 'X' && *str != '0')
		ret += write(1, "0X", 2);
	return (ret + putstr_nbyte(str, len));
}

intmax_t	handle_length_mod(t_flag *flag, va_list ap)
{
	intmax_t	nb;

	if (flag->len[0] == 'h')
	{
		if (flag->len[1] == 'h')
			return (nb = (signed char)va_arg(ap, int));
		else
			return (nb = (short)va_arg(ap, int));
	}
	else if (flag->len[0] == 'l')
	{
		if (flag->len[1] == 'l')
			return (nb = va_arg(ap, long long));
		else
			return (nb = va_arg(ap, long));
	}
	return (nb = va_arg(ap, int));
}

intmax_t	handle_unsigned_length_mod(t_flag *flag, va_list ap)
{
	uintmax_t	nb;

	if (flag->spec == 'p')
	{
		flag->spec = 'x';
		flag->hash = TRUE;
		return (nb = (uintptr_t)va_arg(ap, void *));
	}	
	if (flag->len[0] == 'h')
	{
		if (flag->len[1] == 'h')
			return (nb = (unsigned char)va_arg(ap, int));
		else
			return (nb = (unsigned short)va_arg(ap, int));
	}
	if (flag->len[0] == 'l')
	{
		if (flag->len[1] == 'l')
			return (nb = va_arg(ap, unsigned long long));
		else
			return (nb = va_arg(ap, unsigned long));
	}
	return (nb = va_arg(ap, unsigned int));
}
