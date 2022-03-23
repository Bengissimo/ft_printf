/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:46:49 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/23 10:49:56 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	get_mantissa_zeroes(t_flag *flag, long double nb_dec)
{
	uintmax_t	zeroes;

	if (flag->dot == FALSE)
		flag->prec = 6;
	zeroes = 0;
	while (nb_dec < 0.1 && zeroes < flag->prec)
	{
		nb_dec *= 10.0;
		zeroes++;
	}
	if (flag->prec == zeroes)
		(zeroes)--;
	if (flag->prec < zeroes)
		zeroes = flag->prec;
	return (zeroes);
}

static	void	round_to_prec(t_flag *flag, uintmax_t *nb_int, long double *nb_dec)
{
	uintmax_t	round_down;
	uintmax_t	round_up;
	long double	rounding_coeff;

	rounding_coeff = ft_power(10.0, flag->prec);
	*nb_dec = (*nb_dec) * rounding_coeff;
	round_down = (uintmax_t)(*nb_dec);
	round_up = (uintmax_t)(*nb_dec + 1);
	if ((*nb_dec - round_down) > (round_up - *nb_dec))
	{
		*nb_dec = round_up;
		if (flag->prec == 0)
			(*nb_int)++;
	}
	else if ((*nb_dec - round_down) == (round_up - *nb_dec))
	{
		*nb_dec = round_up; //still not sure if a bankers round needed here?
		if (flag->prec == 0 && (*nb_int + 1) % 2 == 0)
			(*nb_int)++;
	}
	else
		*nb_dec = round_down;
}

static char	*join_and_free_str(char *dst, char *str)
{
	char	*temp;

	temp = dst;
	dst = ft_strjoin(dst, str);
	ft_strdel(&temp);
	return (dst);
}

static char	*join_float_str(t_flag *flag, uintmax_t nb_int, uintmax_t nb_dec, uintmax_t zeroes)
{
	char		*str_dec;
	char		*str_float;
	uintmax_t	i;

	str_float = ft_itoa_base(nb_int, 10);
	if (!(flag->prec == 0 && flag->dot == TRUE))
		str_float = join_and_free_str(str_float, ".");
	if (zeroes > 0)
	{
		i = 0;
		while (i < zeroes)
		{
			str_float = join_and_free_str(str_float, "0");
			i++;
		}
	}
	if (flag->prec > zeroes && flag->prec != 0)
	{
		str_dec = ft_itoa_base((uintmax_t)(nb_dec), 10);
		str_float = join_and_free_str(str_float, str_dec);
		ft_strdel(&str_dec);
	}
	return (str_float);
}

static int	handle_float(t_flag *flag, char *str_float, int negative)
{
	uintmax_t	len;

	len = ft_strlen(str_float);
	if (flag->width > len && flag->dash == TRUE)
		return (handle_width_dash(flag, str_float, negative));
	/*if (flag->width > len && flag->zero == TRUE)
		return (handle_width_zero(flag, str_float, negative));*/
	if (flag->width > len)
		return (handle_width(flag, str_float, negative));
	return (handle_plus_or_space(flag, str_float, negative));
}

int	print_double(t_flag *flag, va_list ap)
{
	long double	nb_dbl;
	uintmax_t	nb_int;
	long double	nb_dec;
	int			negative;
	int			zeroes;
	char		*str_float;
	int			ret;

	negative = FALSE;
	if (flag->len[0] == 'L')
		nb_dbl = va_arg(ap, long double);
	else
		nb_dbl = va_arg(ap, double);
	nb_dbl = abs_value(nb_dbl, &negative);
	nb_int = (uintmax_t)nb_dbl;
	nb_dec = nb_dbl - (uintmax_t)nb_dbl;
	zeroes = get_mantissa_zeroes(flag, nb_dec);
	round_to_prec(flag, &nb_int, &nb_dec);
	str_float = join_float_str(flag, nb_int, (uintmax_t)(nb_dec), zeroes);
	ret = handle_float(flag, str_float, negative);
	ft_strdel(&str_float);
	return (ret);
}
