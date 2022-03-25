/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:05:56 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/25 14:06:39 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	round_to_prec(t_flag *flag, uintmax_t *nb_i, long double *nb_d)
{
	uintmax_t	round_down;
	uintmax_t	round_up;
	long double	rounding_coeff;

	rounding_coeff = ft_power(10.0, flag->prec);
	*nb_d = (*nb_d) * rounding_coeff;
	round_down = (uintmax_t)(*nb_d);
	round_up = (uintmax_t)(*nb_d + 1);
	if ((*nb_d - round_down) > (round_up - *nb_d))
	{
		*nb_d = round_up;
		if (flag->prec == 0)
			(*nb_i)++;
	}
	else if ((*nb_d - round_down) == (round_up - *nb_d))
	{
		*nb_d = round_up;
		if (flag->prec == 0 && (*nb_i + 1) % 2 == 0)
			(*nb_i)++;
	}
	else
		*nb_d = round_down;
}
