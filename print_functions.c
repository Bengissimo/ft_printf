/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:07:09 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/15 10:29:34 by bkandemi         ###   ########.fr       */
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


int	put_format(t_flag *flag, va_list ap)
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
		return (print_c(flag, ap));
	else if (flag->specifier == 's')
		return (print_s(flag, ap));
	else if (flag->specifier == 'p')
		return (print_p(flag, ap));
	else if (flag->specifier == 'd' || flag->specifier == 'i')
		return (print_signed_int(flag, ap));
	else if (flag->specifier == 'u' || flag->specifier == 'o' || flag->specifier == 'x' || flag->specifier == 'X')
		return (print_unsigned_int(flag, ap));
	else if (flag->specifier == 'f')
		return (print_double(flag, ap));
	return (0); //to be deleted
		
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

static intmax_t handle_unsigned_length_mod(t_flag *flag, va_list ap)
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
int	print_int(t_flag *flag, char *str, int len, int negative)
{
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
int	print_signed_int(t_flag *flag, va_list ap)
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
	return (print_int(flag, str, len, negative));
	/*if (flag->precision > len && flag->width > flag->precision
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
	return (handle_plus_or_space(flag, str, len, negative));*/
}

int	print_unsigned_int(t_flag *flag, va_list ap)
{
	uintmax_t	nb;
	char		*str;
	int			len;
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
	len = ft_strlen(str);
	negative = FALSE;
	flag->plus = FALSE;
	flag->space = FALSE;
	if (flag->specifier == 'o')
	{
		if (flag->dot == TRUE && flag->precision == 0 && nb == 0 && flag->hash == FALSE)
			return (0);
		if (flag->hash == TRUE && nb != 0)
			return (write(1, "0", 1) + print_int(flag, str, len, negative));
		return (print_int(flag, str, len, negative));
	}
	if (flag->dot == TRUE && flag->precision == 0 && nb == 0)
		return (0);
	if (flag->hash == TRUE && flag->specifier == 'x' && nb != 0)
		return (write(1, "0x", 2) + print_int(flag, str, len, negative));
	if (flag->hash == TRUE && flag->specifier == 'X' && nb != 0)
		return (write(1, "0X", 2) + print_int(flag, str, len, negative));
	return (print_int(flag, str, len, negative));
}

int	print_double(t_flag *flag, va_list ap)
{
	double nb;
	char *str1;
	char *str2;
	uintmax_t int_nb;
	double dec_nb;
	
	
	uintmax_t precision;
	
	//unsigned long i;

	flag->precision = 10;
	flag->dot = TRUE;
	nb = va_arg(ap, double);

	if (nb < 0)
	{
		nb = -nb;
		write (1, "-", 1);
	}
	int_nb = (uintmax_t)nb;
	dec_nb = nb - int_nb;
	int i = 0;
	while (dec_nb < 0.1)
	{
		dec_nb = dec_nb * 10;
		i++;
	}
	if (flag->precision == i)
		i--;
	if (flag->precision < i)
		i = flag->precision;
	
	
	
	//printf("dec_nb: %f\n", dec_nb);
	
	precision = ft_power(10, 10 - i);
	
	double raw = dec_nb * precision;
	uintmax_t less = (uintmax_t)(raw);
	uintmax_t more = (uintmax_t)(raw + 1);
	/*printf("dec_nb * precision: %f\n", dec_nb * precision);
	printf("int more: %ju\n", more);
	printf("int less: %ju\n", less);
	printf("%f\n", more - (dec_nb * precision));
	printf("%f\n", (dec_nb * precision) - less);
	printf("int_nb: %ju\n", int_nb);*/
	if (((raw) - less) > (more - (raw)))
	{
		raw = more;
		//printf("more: %f\n", dec_nb);
		if (flag->dot == TRUE && flag->precision == 0)
			int_nb += more;
	}
	else if (((raw) - less) == (more - (raw)))
	{
		if ((int_nb + 1) % 2 == 0)
			int_nb++;
	}
	else
	{
		raw = less;
		//printf("less: %f\n", dec_nb);
	}
	
	str1 = ft_itoa_base(int_nb, 10);
	putstr_nbyte(str1, ft_strlen(str1));
	if (flag->precision != 0)
		write(1, ".", 1);
	if (flag->precision >= i)	 						//if precision > 0
		putchar_nbyte('0', i);   //if precision >= zeroes
	if (flag->precision != i){
		str2 = (ft_itoa_base((uintmax_t)(raw), 10)); 	////if precision > 0 && precision > i
		putstr_nbyte(str2, ft_strlen(str2)); 	//if precision > 0 && precision > i
	}
	return (0);
	
}
