/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:40:05 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/15 15:09:39 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	put_neg_sign(int negative)
{
	if (negative == TRUE)
		return (write(1, "-", 1));
	return (0);
}

static double	abs_value_dbl(double nb_dbl, int *negative)
{
	*negative = FALSE;

	if (nb_dbl < 0)
	{
		nb_dbl = -nb_dbl;
		*negative = TRUE;
	}
	return (nb_dbl);
}

static double	abs_value_dbl(double nb_dbl, int *negative)
{
	*negative = FALSE;

	if (nb_dbl < 0)
	{
		nb_dbl = -nb_dbl;
		*negative = TRUE;
	}
	return (nb_dbl);
}

static	int	get_zeroes_after_point(t_flag *flag, double nb_dec)
{
	int	zeroes;

	zeroes = 0;
	while (nb_dec < 0.1)
	{
		nb_dec = nb_dec * 10.0;
		zeroes++;
	}
	if (flag->precision == zeroes)
		zeroes--;
	if (flag->precision < zeroes)
		zeroes = flag->precision;
	return (zeroes);
}

static	double	round_to_precision(t_flag *flag, uintmax_t *nb_int, double *nb_dec, int zeroes)
{
	uintmax_t	round_down;
	uintmax_t	round_up;
	uintmax_t	rounding_coeff;
	
	if (flag->dot == TRUE)
		rounding_coeff = ft_power(10, flag->precision - zeroes);
	else
		rounding_coeff = ft_power(10, 6 - zeroes); //default precision of printf
	*nb_dec = (*nb_dec) * rounding_coeff;
	round_down = (uintmax_t)(*nb_dec);
	round_up  = (uintmax_t)(*nb_dec + 1);
	if (((*nb_dec) - round_down) >= (round_up - (*nb_dec)))
	{
		*nb_dec = round_up;
		if (flag->dot == TRUE && flag->precision == 0)
		{
			if (((*nb_int) + 1) % 2 == 0)
				(*nb_int)++;
		}
	}
	else
		*nb_dec = round_down;
	return (*nb_dec);
}

int	print_double(t_flag *flag, va_list ap)
{
	double nb_dbl;
	char *str1;
	char *str2;
	uintmax_t nb_int;
	double nb_dec;
	int negative;
	int zeroes;

	negative = 0;
	flag->precision = 2;
	flag->dot = TRUE;
	nb_dbl = va_arg(ap, double);
	nb_dbl = abs_value_dbl(nb_dbl, &negative);
	nb_int = (uintmax_t)nb_dbl;
	nb_dec = nb_dbl - nb_int;
	zeroes = get_zeroes_after_point(flag, nb_dec);
	nb_dec = round_to_precision(flag, &nb_int, &nb_dec, zeroes);
	str1 = ft_itoa_base(nb_int, 10);
	putstr_nbyte(str1, ft_strlen(str1));
	if (flag->precision != 0)
		write(1, ".", 1);
	if (flag->precision >= zeroes && flag->dot == TRUE && flag->precision != 0)	 						//if precision > 0
		putchar_nbyte('0', zeroes);   //if precision >= zeroes
	if (flag->precision != zeroes && flag->dot == TRUE && flag->precision != 0)
	{
		str2 = (ft_itoa_base((uintmax_t)(nb_dec), 10)); 	////if precision > 0 && precision > i
		putstr_nbyte(str2, ft_strlen(str2)); 	//if precision > 0 && precision > i
	}
	return (0);
	
}
