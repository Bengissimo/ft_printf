/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_width_flags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:39:30 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/22 13:40:56 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int handle_width(t_flag *flag, char *str, int negative)
{
	int			ret;
	uintmax_t	len;

	ret = 0;
	len = ft_strlen(str);
	if (negative == TRUE)
		ret = putchar_nbyte(' ', flag->width - len - 1) + write(1, "-", 1);
	else if (flag->plus == TRUE)
		ret = putchar_nbyte(' ', flag->width - len - 1) + write(1, "+", 1); //TO DO: check the order of + with print_int!!!
	else
		ret = putchar_nbyte(' ', flag->width - len);
	return (ret + putstr_nbyte(str, len));
}

int handle_width_zero(t_flag *flag, char *str, int negative)
{
	int			ret;
	int			n_zero;
	uintmax_t	len;

	ret = 0;
	len = ft_strlen(str);
	if (flag->plus == TRUE || flag->space == TRUE || negative == TRUE)
		n_zero = flag->width - len - 1;
	else
		n_zero = flag->width - len;
	if (negative == TRUE)
		ret = write(1, "-", 1);
	else if (flag->plus == TRUE)
		ret = write(1, "+", 1);
	else if (flag->space == TRUE)
		ret = write(1, " ", 1);
	return (ret + putchar_nbyte('0', n_zero)+ putstr_nbyte(str, len));
}

int handle_width_dash(t_flag *flag, char *str, int negative)
{
	int			ret;
	int			n_space;
	uintmax_t	len;

	ret = 0;
	len = ft_strlen(str);
	if (flag->plus == TRUE || flag->space == TRUE || negative == TRUE)
		n_space = flag->width - len - 1;
	else
		n_space = flag->width - len;
	if (negative == TRUE)
		ret = write(1, "-", 1);
	else if (flag->plus == TRUE)
		ret = write(1, "+", 1);
	else if (flag->space == TRUE)
		ret = write(1, " ", 1);
	return (ret + putstr_nbyte(str, len) + putchar_nbyte(' ', n_space));
}
