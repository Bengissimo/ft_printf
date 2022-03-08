/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:07:09 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/08 10:58:05 by bkandemi         ###   ########.fr       */
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
		printf("%d", flag->width);
	if (flag->precision > 0)
		printf(".%d", flag->precision);
	printf("length[0]: %c, length[1]: %c", flag->length[0], flag->length[1]);
	fflush(stdout);
	printf(":\n");
	/*printf("ft_str: %s	", flag->str);
	printf("dash: %d, hash: %d, plus: %d, space: %d, zero: %d	", flag->dash, flag->hash, flag->plus, flag->space, flag->zero);
	printf("width: %d	", flag->width);
	printf("precision: %d\n", flag->precision);*/
	//printf("length[0]: %c, length[1]: %c\n", flag->length[0], flag->length[1]);
	//printf("specifier: %c\n", flag->specifier);
}

/*static void	put_fmt_nbr(int nb)
{
	ft_putnbr(nb);
}*/

static intmax_t	abs_value(intmax_t nb, int *negative)
{
	*negative = 0;

	if (nb < 0)
	{
		nb = -nb;
		*negative = 1;
	}
	return (nb);
}


void	put_format(t_flag *flag, va_list ap)
{
	fill(flag);
	check_print(flag);
	//int nb;
	/*if (flag->specifier == 'd')
	{
		nb = va_arg(ap, int);
		if (flag->plus == TRUE && nb >= 0)
		{
			ft_putchar('+');
		}
		put_fmt_nbr(nb);
	}*/
	if (flag->specifier == 'c')
		print_c(flag, ap);
	else if (flag->specifier == 's')
		print_s(flag, ap);
	else if (flag->specifier == 'p')
		print_p(flag, ap);
	else if (flag->specifier == 'd' || flag->specifier == 'i')
		print_int(flag, ap);
	else if (flag->specifier == 'u')
		print_unsigned(flag, ap);
		
}

int	print_c(t_flag *flag, va_list ap)
{
	char c;

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
	char	*s;
	int		len;

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

int print_p(t_flag *flag, va_list ap)
{
	void	*ptr;
	char	*str;
	int		strlen;

	ptr = va_arg(ap, void *);
	str = ft_itoa_base((long)ptr, 16);
	strlen = ft_strlen(str);
	if (flag->width < strlen)
	{
		ft_putstr("0x");
		ft_putstr(str);
	}
	return (ft_strlen(str) + 2);
}

static int	handle_precision(t_flag *flag, char *str, int len, int negative)
{
	int ret;

	ret = 0;
	if (negative == TRUE)
		ret = write(1, "-", 1);
	else if (flag->plus == TRUE)
		ret = write(1, "+", 1);
	else if (flag->space == TRUE)
		ret = write(1, " ", 1);
	return (ret + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len));
}

static int	handle_width_precision_dash(t_flag *flag, char *str, int len, int negative)
{
	int ret;
	int space;

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

static int	handle_width_precision(t_flag *flag, char *str, int len, int negative)
{
	int ret;

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

static int	handle_plus_or_space(t_flag *flag, char *str, int len, int negative)
{
	int ret;

	ret = 0;
	if (negative == TRUE)
		ret = write(1, "-", 1);
	else if (flag->plus == TRUE)
		ret = write(1, "+", 1);
	else if (flag->space == TRUE)
		ret = write(1, " ", 1);
	return (ret + putstr_nbyte(str, len));
}

static int handle_width(t_flag *flag, char *str, int len, int negative)
{
	int ret;
	
	ret = 0;
	if (negative == TRUE)
		ret = putchar_nbyte(' ', flag->width - len - 1) + write(1, "-", 1);
	else if (flag->plus == TRUE)
		ret = write(1, "+", 1) + putchar_nbyte(' ', flag->width - len - 1);
	else
		ret = putchar_nbyte(' ', flag->width - len);
	return (ret + putstr_nbyte(str, len));
}

static int handle_width_zero(t_flag *flag, char *str, int len, int negative)
{
	int ret;
	int n_zero;
	
	ret = 0;
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

static int handle_width_dash(t_flag *flag, char *str, int len, int negative)
{
	int ret;
	int n_space;
	
	ret = 0;
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

static intmax_t handle_u_length_mod(t_flag *flag, va_list ap)
{
	uintmax_t nb;
	
	if (flag->length[0] == 'h')
	{
		if(flag->length[1] == 'h')
			return (nb = (unsigned char)va_arg(ap, int));
		else
			return (nb = (unsigned short)va_arg(ap, int));
	}
	else if (flag->length[0] == 'l')
	{
		if(flag->length[1] == 'l')
			return (nb = va_arg(ap, unsigned long long));
		else
			return (nb = va_arg(ap, unsigned long));
	}
	return (nb = va_arg(ap, unsigned int));
}

int	print_int(t_flag *flag, va_list ap)
{
	intmax_t	nb;
	char		*str;
	int			len;
	int			negative;

	nb = handle_length_mod(flag, ap);
	nb = abs_value(nb, &negative);
	str = ft_itoa_base(nb, 10);
	len = ft_strlen(str);
	if (flag->dot == TRUE && flag->precision == 0 && nb == 0)
		return (0);
	if (flag->precision > len && flag->width > flag->precision
		&& flag->dash == TRUE)
		return (handle_width_precision_dash(flag, str, len, negative));
	if (flag->precision > len && flag->width > flag->precision)
		return (handle_width_precision(flag, str, len, negative));
	if (flag->precision > len)
		return (handle_precision(flag, str, len, negative));
	if (flag->width > len && flag->dash == TRUE)
		return (handle_width_dash(flag, str, len, negative));
	if (flag->width > len && flag->zero == TRUE)
		return (handle_width_zero(flag, str, len, negative));
	if (flag->width > len)
		return (handle_width(flag, str, len, negative));
	return (handle_plus_or_space(flag, str, len, negative));
}

int	print_unsigned(t_flag *flag, va_list ap)
{
	uintmax_t	nb;
	char		*str;
	int			len;
	int			negative;

	nb = handle_u_length_mod(flag, ap);
	str = ft_itoa_base(nb, 10);
	len = ft_strlen(str);
	negative = FALSE;
	flag->plus = FALSE;
	flag->space = FALSE;
	if (flag->dot == TRUE && flag->precision == 0 && nb == 0)
		return (0);
	if (flag->precision > len && flag->width > flag->precision
		&& flag->dash == TRUE)
		return (handle_width_precision_dash(flag, str, len, negative));
	if (flag->precision > len && flag->width > flag->precision)
		return (handle_width_precision(flag, str, len, negative));
	if (flag->precision > len)
		return (handle_precision(flag, str, len, negative));
	if (flag->width > len && flag->dash == TRUE)
		return (handle_width_dash(flag, str, len, negative));
	if (flag->width > len && flag->zero == TRUE)
		return (handle_width_zero(flag, str, len, negative));
	if (flag->width > len)
		return (handle_width(flag, str, len, negative));
	return (handle_plus_or_space(flag, str, len, negative));
}
