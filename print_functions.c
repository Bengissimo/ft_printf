/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:07:09 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/18 13:24:27 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_print(t_flag *flag)
{
	if (flag->dash)
		printf("-");
	if (flag->plus)
		printf("+");
	if(flag->space)
		printf("sp");
	if (flag->width > 0)
		printf("%ju", flag->width);
	if (flag->zero)
		printf("0");
	if (flag->precision > 0)
		printf(".%ju", flag->precision);
	printf("length[0]: %c, length[1]: %c", flag->length[0], flag->length[1]);
	fflush(stdout);
	printf(":\n");
}

static intmax_t	abs_value_int(intmax_t nb, int *negative)
{
	*negative = 0;
	if (nb < 0)
	{
		nb = -nb;
		*negative = 1;
	}
	return (nb);
}


int	put_format(t_flag *flag, va_list ap)
{
	fill(flag);
	check_print(flag);
	if (flag->specifier == 'c')
		return (print_c(flag, ap));
	else if (flag->specifier == 's')
		return (print_s(flag, ap));
	/*else if (flag->specifier == 'p')
		return (print_p(flag, ap));*/
	else if (flag->specifier == 'd' || flag->specifier == 'i')
		return (print_signed_int(flag, ap));
	else if (flag->specifier == 'u' || flag->specifier == 'o' || flag->specifier == 'x' || flag->specifier == 'X' || flag->specifier == 'p')
		return (print_unsigned_int(flag, ap));
	else if (flag->specifier == 'f')
		return (print_double(flag, ap));
	return (0); //to be deleted
}

int	print_c(t_flag *flag, va_list ap)
{
	char	c;

	c = va_arg(ap, int);
	if (flag->width < 1)
	{
		ft_putchar(c);
		return (1);
	}
	if (flag->dash == TRUE)
	{
		ft_putchar(c);
		putchar_nbyte(' ', flag->width - 1);
		return (1);
	}
	putchar_nbyte(' ', flag->width - 1);
	ft_putchar(c);
	return (1);
}

int	print_s(t_flag *flag, va_list ap)
{
	char		*s;
	uintmax_t	len;

	s = va_arg(ap, char *);
	len = ft_strlen(s);
	if (flag->precision > 0 && flag->precision > len)
		len = flag->precision;
	if (flag->width <= len)
		return (putstr_nbyte(s, len));
	if (flag->dash == TRUE) // width > len
		return(putstr_nbyte(s, len) + putchar_nbyte(' ', flag->width - len));
	return (putchar_nbyte(' ', flag->width - len) + putstr_nbyte(s, len));
}

/*int print_p(t_flag *flag, va_list ap)
{
	//void	*ptr;
	uintptr_t arg;
	char	*str;
	int		strlen;
	int negative;
	negative = FALSE;

	//ptr = va_arg(ap, void *);
	arg = (uintptr_t)va_arg(ap, void *);
	str = ft_itoa_base((uintmax_t)arg, 16);
	strlen = ft_strlen(str);
	/*if ((int)flag->width < strlen)
	{
		ft_putstr("0x");
		ft_putstr(str);
	}*/
	return (write(1, "0x", 2) + handle_int(flag, str, negative));
}*/

static int	handle_precision(t_flag *flag, char *str, int negative)
{
	int			ret;
	uintmax_t	len;

	ret = 0;
	len = ft_strlen(str);
	if (negative == TRUE)
		ret = write(1, "-", 1);
	else if (flag->plus == TRUE)
		ret = write(1, "+", 1);
	else if (flag->space == TRUE)
		ret = write(1, " ", 1);
	return (ret + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len));
}

static int	handle_width_precision_dash(t_flag *flag, char *str, int negative)
{
	int			ret;
	int			space;
	uintmax_t	len;

	len = ft_strlen(str);
	if (flag->plus == TRUE || flag->space == TRUE || negative == TRUE)
		space = flag->width - flag->precision - 1;
	else
		space = flag->width - flag->precision;
	ret = 0;
	if (negative == TRUE)
		ret = write(1, "-", 1);
	else if (flag->plus == TRUE)
		ret = write(1, "+", 1);
	else if (flag->space == TRUE)
		ret = write(1, " ", 1);
	return (ret + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len) + putchar_nbyte(' ', space));
}

static int	handle_width_precision(t_flag *flag, char *str, int negative)
{
	int ret;
	uintmax_t	len;

	ret = 0;
	len = ft_strlen(str);
	if (flag->plus == TRUE || flag->space == TRUE || negative == TRUE)
		ret = putchar_nbyte(' ', flag->width - flag->precision - 1);
	else
		ret = putchar_nbyte(' ', flag->width - flag->precision);
	if (negative == TRUE)
		ret += write(1, "-", 1);
	else if (flag->plus == TRUE)
		ret += write(1, "+", 1);
	else if (flag->space == TRUE)
		ret += write(1, " ", 1);
	return (ret + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len));
}

static int	handle_plus_or_space(t_flag *flag, char *str, int negative)
{
	int			ret;
	uintmax_t	len;

	len = ft_strlen(str);
	ret = 0;
	if (negative == TRUE)
		ret = write(1, "-", 1);
	else if (flag->plus == TRUE)
		ret = write(1, "+", 1);
	else if (flag->space == TRUE)
		ret = write(1, " ", 1);
	return (ret + putstr_nbyte(str, len));
}

static int handle_width(t_flag *flag, char *str, int negative)
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

static int handle_width_zero(t_flag *flag, char *str, int negative)
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

static int handle_width_dash(t_flag *flag, char *str, int negative)
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

static intmax_t handle_length_mod(t_flag *flag, va_list ap)
{
	intmax_t nb;

	if (flag->length[0] == 'h')
	{
		if(flag->length[1] == 'h')
			return (nb = (signed char)va_arg(ap, int));
		else
			return (nb = (short)va_arg(ap, int));
	}
	else if (flag->length[0] == 'l')
	{
		if(flag->length[1] == 'l')
			return (nb = va_arg(ap, long long));
		else
			return (nb = va_arg(ap, long));
	}
	return (nb = va_arg(ap, int));
}

static intmax_t handle_unsigned_length_mod(t_flag *flag, va_list ap) //p'yi ekleyince adi kotu oldu
{
	uintmax_t nb;

	if (flag->specifier == 'p')
	{
		flag->specifier = 'x';
		flag->hash = TRUE;
		return (nb = (uintptr_t)va_arg(ap, void *));
	}	
	if (flag->length[0] == 'h')
	{
		if(flag->length[1] == 'h')
			return (nb = (unsigned char)va_arg(ap, int));
		else
			return (nb = (unsigned short)va_arg(ap, int));
	}
	if (flag->length[0] == 'l')
	{
		if(flag->length[1] == 'l')
			return (nb = va_arg(ap, unsigned long long));
		else
			return (nb = va_arg(ap, unsigned long));
	}
	return (nb = va_arg(ap, unsigned int));
}

int	handle_int(t_flag *flag, char *str, int negative)
{
	uintmax_t	len;

	len = ft_strlen(str);
	if (flag->precision > len && flag->width > flag->precision
		&& flag->dash == TRUE)
		return (handle_width_precision_dash(flag, str, negative));
	if (flag->precision > len && flag->width > flag->precision)
		return (handle_width_precision(flag, str, negative));
	if (flag->precision > len)
		return (handle_precision(flag, str, negative));
	if (flag->width > len && flag->dash == TRUE)
		return (handle_width_dash(flag, str, negative));
	if (flag->width > len && flag->zero == TRUE)
		return (handle_width_zero(flag, str, negative));
	if (flag->width > len)
		return (handle_width(flag, str, negative));
	return (handle_plus_or_space(flag, str, negative));
}
int	print_signed_int(t_flag *flag, va_list ap)
{
	intmax_t	nb;
	char		*str;
	int			negative;
	int			ret;

	nb = handle_length_mod(flag, ap);
	nb = abs_value_int(nb, &negative);
	if (flag->dot == TRUE && flag->precision == 0 && nb == 0)
		return (0);
	str = ft_itoa_base(nb, 10);
	ret = handle_int(flag, str, negative);
	ft_strdel(&str);
	return (ret);
}

int	print_unsigned_int(t_flag *flag, va_list ap)
{
	uintmax_t	nb;
	char		*str;
	int			negative;

	nb = handle_unsigned_length_mod(flag, ap);
	if (flag->specifier == 'o')
		str = ft_itoa_base(nb, 8);
	else if (flag->specifier == 'x')
		str = ft_itoa_base(nb, 16);
	else if (flag->specifier == 'X')
		str = ft_itoa_base_upper(nb, 16);
	else
		str = ft_itoa_base(nb, 10);
	negative = FALSE;
	flag->plus = FALSE;
	flag->space = FALSE;
	if (flag->specifier == 'o')
	{
		if (flag->dot == TRUE && flag->precision == 0 && nb == 0 && flag->hash == FALSE)
			return (0);
		if (flag->hash == TRUE && nb != 0)
			return (write(1, "0", 1) + handle_int(flag, str, negative));
		return (handle_int(flag, str, negative));
	}
	if (flag->dot == TRUE && flag->precision == 0 && nb == 0)
		return (0);
	if (flag->hash == TRUE && flag->specifier == 'x' && nb != 0)
		return (write(1, "0x", 2) + handle_int(flag, str, negative));
	if (flag->hash == TRUE && flag->specifier == 'X' && nb != 0)
		return (write(1, "0X", 2) + handle_int(flag, str, negative));
	return (handle_int(flag, str, negative));
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
	uintmax_t zeroes;

	if (flag->dot == FALSE)
		flag->precision = 6;
	zeroes = 0;
	while (nb_dec < 0.1 && zeroes < flag->precision)
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

static char *join_and_free_str(char *dst, char *str)
{
	char	*temp;

	temp = dst;
	dst = ft_strjoin(dst, str);
	ft_strdel(&temp);
	return (dst);
}

static char *join_float_str(t_flag *flag, uintmax_t nb_int, uintmax_t nb_dec, uintmax_t zeroes)
{
	char		*str_dec;
	char		*str_float;
	uintmax_t	i;
	
	str_float = ft_itoa_base(nb_int, 10);
	if (!(flag->precision == 0 && flag->dot == TRUE))
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
	if (flag->precision > zeroes && flag->precision != 0)
	{
		str_dec = ft_itoa_base((uintmax_t)(nb_dec), 10);
		str_float = join_and_free_str(str_float, str_dec);
		ft_strdel(&str_dec);
	}
	return (str_float);
}

static int handle_float(t_flag *flag, char *str_float, int negative)
{
	uintmax_t	len;

	len = ft_strlen(str_float);
	if (flag->width > len && flag->dash == TRUE)
		return (handle_width_dash(flag, str_float, negative));
	if (flag->width > len && flag->zero == TRUE)
		return (handle_width_zero(flag, str_float, negative));
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
	char 		*str_float;
	int			ret;

	negative = FALSE;
	if (flag->length[0] == 'L')
		nb_dbl = va_arg(ap, long double);
	else
		nb_dbl = va_arg(ap, double);
	nb_dbl = abs_value_dbl(nb_dbl, &negative);
	nb_int = (uintmax_t)nb_dbl;
	nb_dec = nb_dbl - (uintmax_t)nb_dbl;
	zeroes = get_mantissa_zeroes(flag, nb_dec);
	round_to_precision(flag, &nb_int, &nb_dec);
	str_float = join_float_str(flag, nb_int, (uintmax_t)(nb_dec), zeroes);
	ret = handle_float(flag, str_float, negative);
	ft_strdel(&str_float);
	return (ret);
}
