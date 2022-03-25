/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_other_flags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:39:41 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/25 12:55:44 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_flags(t_flag *flag, char *str, int negative)
{
	if (negative == TRUE)
		return (write(1, "-", 1));
	if (flag->plus == TRUE)
		return (write(1, "+", 1));
	if (flag->space == TRUE)
		return (write(1, " ", 1));
	if (flag->spec == 'p')
		return (write(1, "0x", 2));
	if (flag->hash == TRUE && *str != '0')
	{
		if (flag->spec == 'x')
			return (write(1, "0x", 2));
		if (flag->spec == 'X')
			return (write(1, "0X", 2));
		if (flag->spec == 'o' && flag->prec <= (int)ft_strlen(str))
			return (write(1, "0", 1));
	}
	return (0);
}

int	handle_plus_space_hash(t_flag *flag, char *str, int negative)
{
	int	ret;
	int	len;

	ret = handle_flags(flag, str, negative);
	len = ft_strlen(str);
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
		return (nb = (uintptr_t)va_arg(ap, void *));
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
