/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_precision_flags.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:36:25 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/23 21:04:57 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static uintmax_t	calc_len(t_flag *flag, char *str)
{
	if (*str == '0' && flag->dot == TRUE && flag->prec == 0)
	{
		if (flag->hash == TRUE && flag->spec == 'o')
			return(ft_strlen(str));
		return (0);
	}
	return (ft_strlen(str));
}

static int	calc_space_padding(t_flag *flag, char *str, int neg)
{
	if (flag->width > flag->prec)
	{
		if (flag->hash == TRUE && *str != '0')
		{
			if (flag->spec == 'x' || flag->spec == 'X')
				return (flag->width - flag->prec - 2);
		}
		if (flag->plus == TRUE || neg == TRUE || flag->space == TRUE)
			return (flag->width - flag->prec - 1);
		return (flag->width - flag->prec);
	}
	return (0);
}

static int	handle_flags(t_flag *flag, char *str, int negative)
{
	if (negative == TRUE)
		return (write(1, "-", 1));
	if (flag->plus == TRUE)
		return (write(1, "+", 1));
	if (flag->space == TRUE)
		return (write(1, " ", 1));
	if (flag->hash == TRUE && *str != '0')
	{
		if (flag->spec == 'x')
			return (write(1, "0x", 2));
		if (flag->spec == 'X')
			return (write(1, "0X", 2));
		if (flag->spec == 'o' && flag->dot == FALSE)
			return (write(1, "0", 1));
	}
	return (0);
}

int	handle_precision(t_flag *flag, char *str, int negative)
{
	int			ret;
	uintmax_t	len;
	int 		space;

	ret = 0;
	len = calc_len(flag, str);
	space = calc_space_padding(flag, str, negative);
	if (flag->dash == FALSE)
	{
		ret += putchar_nbyte(' ', space);
		ret += handle_flags(flag, str, negative);
		ret += putchar_nbyte('0', flag->prec - len);
		ret += putstr_nbyte(str, len);
	}
	if (flag->dash == TRUE)
	{
		ret += handle_flags(flag, str, negative);
		ret += putchar_nbyte('0', flag->prec - len);
		ret += putstr_nbyte(str, len);
		ret += putchar_nbyte(' ', space);
	}
	return (ret);
}
