/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 10:40:05 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/16 08:53:12 by bkandemi         ###   ########.fr       */
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

static	int	get_zeroes_after_point(double nb_dec)
{
	int	zeroes;

	zeroes = 0;
	while (nb_dec < 0.1)
	{
		nb_dec = nb_dec * 10.0;
		zeroes++;
	}
	return (zeroes);
}

static	void	round_to_precision(t_flag *flag, uintmax_t *nb_int, double *nb_dec, int *zeroes)  //remove zeroes 
{
	uintmax_t	round_down;
	uintmax_t	round_up;
	uintmax_t	rounding_coeff;

	if (flag->dot == FALSE)
		flag->precision = 6;
	if (flag->precision == *zeroes)
		(*zeroes)--;
	else if (flag->precision < *zeroes)
		*zeroes = flag->precision;
	rounding_coeff = ft_power(10, flag->precision);
	*nb_dec = (*nb_dec) * rounding_coeff;
	printf("decnb: %f\n", *nb_dec);

	round_down = (uintmax_t)*nb_dec;
	round_up  = (uintmax_t)(*nb_dec + 1);
	printf("%f\n", (*nb_dec) - round_down);
	printf("%f\n", round_up - (*nb_dec));
	if (((*nb_dec) - round_down) > (round_up - (*nb_dec)))
	{
		*nb_dec = round_up;
		//printf("nb_dec: %f\n", *nb_dec);
		if (flag->dot == TRUE && flag->precision == 0)
				(*nb_int)++;
	}
	else if (((*nb_dec) - round_down) == (round_up - (*nb_dec)))
	{
		*nb_dec = round_up;
		if (flag->dot == TRUE && flag->precision == 0)
		{
			if (((*nb_int) + 1) % 2 == 0)
				(*nb_int)++;
		}
	}
	else{
		*nb_dec = round_down;
	}
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
	//flag->precision = 5;
	//flag->dot = TRUE;
	nb_dbl = va_arg(ap, double);
	nb_dbl = abs_value_dbl(nb_dbl, &negative);
	nb_int = (uintmax_t)nb_dbl;
	nb_dec = nb_dbl - nb_int;
	zeroes = get_zeroes_after_point(nb_dec);
	
	
	round_to_precision(flag, &nb_int, &nb_dec, &zeroes);
	printf("decnb: %f\n", nb_dec);
	put_neg_sign(negative);
	str1 = ft_itoa_base(nb_int, 10);
	putstr_nbyte(str1, ft_strlen(str1));
	if (!(flag->precision == 0 && flag->dot == TRUE))
		write(1, ".", 1);
	putchar_nbyte('0', zeroes);   //if precision >= zeroes
	if (flag->precision > zeroes && flag->precision != 0)
	{
		str2 = (ft_itoa_base((uintmax_t)(nb_dec), 10)); 	////if precision > 0 && precision > i
		putstr_nbyte(str2, ft_strlen(str2)); 	//if precision > 0 && precision > i
	}
	return (0);
	
}