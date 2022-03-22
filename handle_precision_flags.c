/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_precision_flags.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:36:25 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/22 13:57:52 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_precision(t_flag *flag, char *str, int negative)
{
	int			ret;
	uintmax_t	len;

	ret = 0;
	len = ft_strlen(str);
	if (negative == TRUE)
		ret = write(1, "-", 1);
	else if (flag->plus == TRUE)
		ret = write(1, "+", 1);
	else if (flag->space == TRUE)
		ret = write(1, " ", 1);
	return (ret + putchar_nbyte('0', flag->prec - len) + putstr_nbyte(str, len));
}

int	handle_width_precision_dash(t_flag *flag, char *str, int negative)
{
	int			ret;
	int			space;
	uintmax_t	len;

	len = ft_strlen(str);
	if (flag->plus == TRUE || flag->space == TRUE || negative == TRUE)
		space = flag->width - flag->prec - 1;
	else
		space = flag->width - flag->prec;
	ret = 0;
	if (negative == TRUE)
		ret = write(1, "-", 1);
	else if (flag->plus == TRUE)
		ret = write(1, "+", 1);
	else if (flag->space == TRUE)
		ret = write(1, " ", 1);
	return (ret + putchar_nbyte('0', flag->prec - len) + putstr_nbyte(str, len) + putchar_nbyte(' ', space));
}

int	handle_width_precision(t_flag *flag, char *str, int negative)
{
	int ret;
	uintmax_t	len;

	ret = 0;
	len = ft_strlen(str);
	if (flag->plus == TRUE || flag->space == TRUE || negative == TRUE)
		ret = putchar_nbyte(' ', flag->width - flag->prec - 1);
	else
		ret = putchar_nbyte(' ', flag->width - flag->prec);
	if (negative == TRUE)
		ret += write(1, "-", 1);
	else if (flag->plus == TRUE)
		ret += write(1, "+", 1);
	else if (flag->space == TRUE)
		ret += write(1, " ", 1);
	return (ret + putchar_nbyte('0', flag->prec - len) + putstr_nbyte(str, len));
}
