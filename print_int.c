/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:50:25 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/22 17:37:55 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_int(t_flag *flag, char *str, int negative)
{
	uintmax_t	len;
	int			ret;

	len = ft_strlen(str);
	if (flag->prec > len && flag->width > flag->prec && flag->dash == TRUE)
		ret = handle_width_precision_dash(flag, str, negative);
	else if (flag->prec > len && flag->width > flag->prec)
		ret = handle_width_precision(flag, str, negative);
	else if (flag->prec > len)
		ret = handle_precision(flag, str, negative);
	else if (flag->width > len && flag->dash == TRUE)
		ret = handle_width_dash(flag, str, negative);
	else if (flag->width > len && flag->zero == TRUE)
		ret = handle_width_zero(flag, str, negative);
	else if (flag->width > len)
		ret = handle_width(flag, str, negative);
	else
		ret = handle_plus_or_space(flag, str, negative);
	ft_strdel(&str);
	return (ret);
}

int	print_signed_int(t_flag *flag, va_list ap)
{
	intmax_t	nb;
	char		*str;
	int			negative;

	nb = handle_length_mod(flag, ap);
	nb = (intmax_t)abs_value((intmax_t)nb, &negative);
	if (flag->dot == TRUE && flag->prec == 0 && nb == 0)
		return (0);
	str = ft_itoa_base(nb, 10);
	return (handle_int(flag, str, negative));
}

static int	handle_uint(t_flag *flag, char *str, int negative)
{
	if (flag->spec == 'o')
	{
		if (flag->dot == TRUE && flag->prec == 0
			&& *str == '0' && flag->hash == FALSE)
		{
			ft_strdel(&str);
			return (0);
		}
		if (flag->hash == TRUE && *str != '0')
			return (write(1, "0", 1) + handle_int(flag, str, negative));
		return (handle_int(flag, str, negative));
	}
	if (flag->dot == TRUE && flag->prec == 0 && *str == '0')
	{
		if (flag->width > 0)
		{
			ft_strdel(&str);
			return (putchar_nbyte(' ', flag->width));
		}
		ft_strdel(&str);
		return (0);
	}
	return (handle_int(flag, str, negative));
}

int	print_unsigned_int(t_flag *flag, va_list ap)
{
	uintmax_t	nb;
	char		*str;
	int			negative;
	
	nb = handle_unsigned_length_mod(flag, ap);
	if (flag->spec == 'o')
		str = ft_itoa_base(nb, 8);
	else if (flag->spec == 'x')
		str = ft_itoa_base(nb, 16);
	else if (flag->spec == 'X')
		str = ft_itoa_base_upper(nb, 16);
	else
		str = ft_itoa_base(nb, 10);
	negative = FALSE;
	flag->plus = FALSE;
	flag->space = FALSE;
	return (handle_uint(flag, str, negative));
}
