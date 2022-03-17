/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:40:05 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/17 09:59:19 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	put_neg_sign(int negative)
{
	if (negative == TRUE)
		return (write(1, "-", 1));
	return (0);
}

static long double	abs_value_dbl(long double nb_dbl, int *negative)
{
	*negative = FALSE;

	if (nb_dbl < 0)
	{
		nb_dbl = -nb_dbl;
		*negative = TRUE;
	}
	return (nb_dbl);
}

static	int	get_mantissa_zeroes(t_flag *flag, long double nb_dec)
{
	int	zeroes;

	if (flag->dot == FALSE)
		flag->precision = 6;
	zeroes = 0;
	while (nb_dec < 0.1)
	{
		nb_dec *= 10.0;
		zeroes++;
	}
	if (flag->precision == zeroes)
		(zeroes)--;
	if (flag->precision < zeroes)
		zeroes = flag->precision;
	return (zeroes);
}

static	void	round_to_precision(t_flag *flag, uintmax_t *nb_int, long double *nb_dec)  //remove zeroes 
{
	uintmax_t	round_down;
	uintmax_t	round_up;
	long double	rounding_coeff;

	rounding_coeff = ft_power(10.0, flag->precision);
	*nb_dec = (*nb_dec) * rounding_coeff;
	round_down = (uintmax_t)*nb_dec;
	round_up  = (uintmax_t)(*nb_dec + 1);
	if ((*nb_dec - round_down) > (round_up - *nb_dec))
	{
		*nb_dec = round_up;
		if (flag->precision == 0)
			(*nb_int)++;
	}
	else if ((*nb_dec - round_down) == (round_up - *nb_dec))
	{
		*nb_dec = round_up; //still not sure if a bankers round needed here?
		if (flag->precision == 0 && (*nb_int + 1) % 2 == 0)
			(*nb_int)++;
	}
	else
		*nb_dec = round_down;
}

int	print_double(t_flag *flag, va_list ap)
{
	long double	nb_dbl;
	char		*str1;
	char		*str2;
	uintmax_t	nb_int;
	long double	nb_dec;
	int			negative;
	int			zeroes;

	negative = 0;
	nb_dbl = va_arg(ap, double);
	nb_dbl = abs_value_dbl(nb_dbl, &negative);
	nb_int = (uintmax_t)nb_dbl;
	nb_dec = nb_dbl - nb_int;
	zeroes = get_mantissa_zeroes(flag, nb_dec);
	round_to_precision(flag, &nb_int, &nb_dec);
	put_neg_sign(negative);
	str1 = ft_itoa_base(nb_int, 10);
	putstr_nbyte(str1, ft_strlen(str1));
	if (!(flag->precision == 0 && flag->dot == TRUE))
		write(1, ".", 1);
	putchar_nbyte('0', zeroes);
	if (flag->precision > zeroes && flag->precision != 0)
	{
		str2 = (ft_itoa_base((uintmax_t)(nb_dec), 10));
		putstr_nbyte(str2, ft_strlen(str2));
	}
	return (0);
}
