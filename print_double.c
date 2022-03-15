/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:40:05 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/15 09:03:06 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	put_neg_sign(double nb_dbl, int negative)
{
	if (negative == TRUE)
		return (write(1, "-", 1));
	return (0);
}

static double	abs_value(double nb_dbl, int *negative)
{
	*negative = FALSE;

	if (nb_dbl < 0)
	{
		nb_dbl = -nb_dbl;
		*negative = TRUE;
	}
	return (nb_dbl);
}

static	double	get_after_point(double nb_dbl)
{
	uintmax_t	nb_int;

	nb_int = (uintmax_t)nb_dbl;
	return (nb_dbl - nb_int);
}

static	int	get_zeroes_after_point(t_flag flag, double nb_dbl)
{
	double		nb_dec;
	int			zeroes;
	
	nb_dec = get_after_point(nb_dbl);
	zeroes = 0;
	while (nb_dec < 0.1)
	{
		nb_dec = nb_dec * 10.0;
		zero_count++;
	}
	if (flag->precision == zeroes)
		zeroes--;
	if (flag->precision < i)
		zeroes = flag->precision;
	return (zeroes);
}

static	double	round_to_precision(t_flag *flag, double *nb_dbl)
{
	uintmax_t	round_down;
	uintmax_t	round_up;
	double		nb_dec;
	uintmax_t	nb_int;
	double		raw;
	int			zeroes;
	uintmax_t	rounding_coefficient;
	
	zeroes = get_zeroes_after_point(*nb_dbl);
	if (flag->dot == TRUE)
		rounding_coeff = ft_power(10, flag->precision - zeroes);
	else
		rounding_coeff = ft_power(10, 6 - zeroes); //default precision of printf
	raw = nb_dec * rounding_coefficient;
	round_down = (uintmax_t)(raw);
	round_up  = (uintmax_t)(raw + 1);
	nb_int = (uintmax_t)(*nb_dbl);
	if ((raw - round_down) > (round_up - raw))
	{
		raw = round_up;
		if (flag->dot == TRUE && flag->precision == 0)  //????????
			nb_int += round_up;
	}
	else if ((raw - round_down) == (round_up - raw))
	{
		if ((nb_int + 1) % 2 == 0)
			nb_int++;
	}
	else
		raw = round_down;
	return (raw);
}

int	print_double(t_flag *flag, va_list ap)
{
	double	nb_dbl;
	int		negative;
	
	char	*str1;
	char	*str2;
	uintmax_t nb_int;
	double nb_dec;
	uintmax_t precision;
	
	flag->precision = 0;
	flag->dot = FALSE;
	nb_dbl = va_arg(ap, double);
	nb_dbl = abs_value(nb_dbl, &negative);
	nb_dec = round_to_precision(flag, &nb_dbl);

	put_neg_sign(nb_dbl, negative);
	str1 = ft_itoa_base((uintmax_t)nb_dbl, 10);
	putstr_nbyte(str1, ft_strlen(str1));
	write(1, ".", 1); 						//if precision > 0
	putchar_nbyte('0', i);
	str2 = (ft_itoa_base((uintmax_t)(nb_dec), 10)); 	//if precision > 0
	putstr_nbyte(str2, ft_strlen(str2)); 	//if precision > 0
	return (0);
	
}