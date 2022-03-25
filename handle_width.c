/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:39:30 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/25 12:56:02 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	calc_padding(t_flag *flag, char *str, uintmax_t len, int neg)
{
	if (flag->hash == TRUE && *str != '0')
	{
		if (flag->spec == 'x' || flag->spec == 'X')
			return (flag->width - len - 2);
		if (flag->spec == 'o')
			return (flag->width - len - 1);
	}
	if (flag->plus == TRUE || neg == TRUE || flag->space == TRUE)
		return (flag->width - len - 1);
	if (flag->spec == 'p')
		return (flag->width - len - 2);
	return (flag->width - len);
}

int	handle_width(t_flag *flag, char *str, int negative)
{
	int	ret;
	int	len;
	int	pad_size;

	ret = 0;
	len = ft_strlen(str);
	pad_size = calc_padding(flag, str, len, negative);
	if (flag->zero == FALSE && flag->dash == FALSE)
		ret = putchar_nbyte(' ', pad_size);
	ret += handle_flags(flag, str, negative);
	if (flag->zero == TRUE)
		ret = ret + putchar_nbyte('0', pad_size);
	if (flag->dash == TRUE)
		return (ret + putstr_nbyte(str, len) + putchar_nbyte(' ', pad_size));
	return (ret + putstr_nbyte(str, len));
}
