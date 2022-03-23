/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_width_flags.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:39:30 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/23 11:51:30 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	calc_space_or_zero(t_flag *flag, uintmax_t len, int neg)
{
	if (flag->hash == TRUE && (flag->spec =='x' || flag->spec =='X'))
		return (flag->width - len - 2);
	if (flag->hash == TRUE && flag->spec =='o')
		return (flag->width - len - 1);
	if (flag->plus == TRUE || neg == TRUE || flag->space == TRUE)
		return (flag->width - len - 1);
	return (flag->width - len);
}

int	handle_width(t_flag *flag, char *str, int negative)
{
	int			ret;
	uintmax_t	len;
	int			n_space;

	ret = 0;
	len = ft_strlen(str);
	n_space = calc_space_or_zero(flag, len, negative);
	if (flag->zero == FALSE)
		ret = putchar_nbyte(' ', n_space);
	if (negative == TRUE)
		ret += write(1, "-", 1);
	else if (flag->plus == TRUE)
		ret += write(1, "+", 1);
	else if (flag->space == TRUE)
		ret += write(1, " ", 1); //TO DO: check the order of + with print_int!!!
	else if (flag->hash == TRUE && flag->spec =='x')
		ret += write(1, "0x", 2);
	else if (flag->hash == TRUE && flag->spec =='X')
		ret += write(1, "0X", 2);
	else if (flag->hash == TRUE && flag->spec =='o')
		ret += write(1, "0", 1);
	if (flag->zero == TRUE)
		ret = ret + putchar_nbyte('0', n_space);
	return (ret + putstr_nbyte(str, len));
}

/*int	handle_width_zero(t_flag *flag, char *str, int negative)
{
	int			ret;
	int			n_zero;
	uintmax_t	len;
	char		space

	ret = 0;
	len = ft_strlen(str);
	n_zero = calc_space_or_zero(flag, &len, &negative);
	if (flag->plus == TRUE || flag->space == TRUE || negative == TRUE)
		n_zero = flag->width - len - 1;
	else if (flag->hash == TRUE)
		n_zero = flag->width - len - 2;
	else
		n_zero = flag->width - len;
	if (negative == TRUE)
		ret = write(1, "-", 1);
	else if (flag->plus == TRUE)
		ret = write(1, "+", 1);
	else if (flag->space == TRUE)
		ret = write(1, " ", 1);
	else if (flag->hash == TRUE && flag->spec =='x')
		ret = write(1, "0x", 2);
	else if (flag->hash == TRUE && flag->spec =='X')
		ret = write(1, "0X", 2);
	else if (flag->hash == TRUE && flag->spec =='o')
		ret = write(1, "0", 1);
	return (ret + putchar_nbyte('0', n_zero) + putstr_nbyte(str, len));
}*/

int	handle_width_dash(t_flag *flag, char *str, int negative)
{
	int			ret;
	int			n_space;
	uintmax_t	len;

	ret = 0;
	len = ft_strlen(str);
	n_space = calc_space_or_zero(flag, len, negative);
	if (negative == TRUE)
		ret = write(1, "-", 1);
	else if (flag->plus == TRUE)
		ret = write(1, "+", 1);
	else if (flag->space == TRUE)
		ret = write(1, " ", 1);
	else if (flag->hash == TRUE && flag->spec =='x')
		ret = write(1, "0x", 2);
	else if (flag->hash == TRUE && flag->spec =='X')
		ret = write(1, "0X", 2);
	else if (flag->hash == TRUE && flag->spec =='o')
		ret = write(1, "0", 1);
	return (ret + putstr_nbyte(str, len) + putchar_nbyte(' ', n_space));
}
