/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:46:49 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/25 14:07:44 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	get_mantissa_zeroes(t_flag *flag, long double nb_dec)
{
	int	zeroes;

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

static char	*join_and_free_str(char *dst, char *str)
{
	char	*temp;

	temp = dst;
	dst = ft_strjoin(dst, str);
	ft_strdel(&temp);
	return (dst);
}

static char	*join_float_str(t_flag *f, uintmax_t ni, uintmax_t nd, int z)
{
	char	*str_dec;
	char	*str_float;
	int		i;

	str_float = ft_itoa_base(ni, 10);
	if (!(f->prec == 0 && f->dot == TRUE))
		str_float = join_and_free_str(str_float, ".");
	if (z > 0)
	{
		i = 0;
		while (i < z)
		{
			str_float = join_and_free_str(str_float, "0");
			i++;
		}
	}
	if (f->prec > z && f->prec != 0)
	{
		str_dec = ft_itoa_base((uintmax_t)(nd), 10);
		str_float = join_and_free_str(str_float, str_dec);
		ft_strdel(&str_dec);
	}
	return (str_float);
}

static int	handle_float(t_flag *flag, char *str_float, int negative)
{
	int	len;

	len = ft_strlen(str_float);
	if (flag->width > len)
		return (handle_width(flag, str_float, negative));
	return (handle_plus_space_hash(flag, str_float, negative));
}

int	print_float(t_flag *flag, va_list ap)
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
