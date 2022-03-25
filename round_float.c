/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:05:56 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/25 15:56:50 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double	get_decimal_from_float(long double nb_dbl)
{
	return (nb_dbl - (uintmax_t)nb_dbl);
}

long double	round_to_prec(t_flag *flag, long double nb_dbl)
{
	uintmax_t	round_down;
	uintmax_t	round_up;
	uintmax_t	nb_dec;

	nb_dec = get_decimal_from_float(nb_dbl);
	nb_dec = nb_dec * ft_power(10.0, flag->prec);
	round_down = (uintmax_t)(nb_dec);
	round_up = (uintmax_t)(nb_dec + 1);
	if ((nb_dec - round_down) > (round_up - nb_dec))
	{
		nb_dec = round_up;
		if (flag->prec == 0)
			(nb_dbl)++;
	}
	else if ((nb_dbl - round_down) == (round_up - nb_dbl))
	{
		nb_dec = round_up;
		if (flag->prec == 0 && ((uintmax_t)nb_dbl + 1) % 2 == 0)
			(nb_dbl)++;
	}
	else
		nb_dec = round_down;
	return (nb_dec);
}
