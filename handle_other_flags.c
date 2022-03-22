/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_other_flags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:39:41 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/22 14:05:38 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_plus_or_space(t_flag *flag, char *str, int negative)
{
	int			ret;
	uintmax_t	len;

	len = ft_strlen(str);
	ret = 0;
	if (negative == TRUE)
		ret = write(1, "-", 1);
	else if (flag->plus == TRUE)
		ret = write(1, "+", 1);
	else if (flag->space == TRUE)
		ret = write(1, " ", 1);
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
