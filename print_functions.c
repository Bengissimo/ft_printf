/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:07:09 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/01 15:13:17 by bkandemi         ###   ########.fr       */
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

static int	abs_value(int nb, int *negative)
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
int print_int(t_flag *flag, va_list ap)
{
	int		nb;
	char	*str;
	int		len;
	int		negative;

	nb = va_arg(ap, int);
	nb = abs_value(nb, &negative);
	str = ft_itoa(nb);
	len  = ft_strlen(str);
	
	if (flag->precision > 0 && flag->precision > len) //if precision true ignore 0 flag
	{
		if (flag->width > flag->precision)
		{
			if (flag->dash == TRUE)
			{
				if (flag->plus == TRUE && negative == FALSE)
					return (write(1, "+", 1) + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len) + putchar_nbyte(' ', flag->width - flag->precision - 1) + negative);
				if (flag->space == TRUE && negative == FALSE)
					return (write(1, " ", 1) + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len) + putchar_nbyte(' ', flag->width - flag->precision - 1));
				if (negative == TRUE)
					return (write(1, "-", 1) + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len) + putchar_nbyte(' ', flag->width - flag->precision - negative));
				return (putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len) + putchar_nbyte(' ', flag->width - flag->precision - negative));
			}
			if (flag->plus == TRUE && negative == FALSE)
				return (putchar_nbyte(' ', flag->width - flag->precision - 1) + write(1, "+", 1) + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len));
			if (flag->space == TRUE && negative == FALSE)
				return (putchar_nbyte(' ', flag->width - flag->precision - 1) + write(1, " ", 1) + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len));
			if (negative == TRUE)
				return (putchar_nbyte(' ', flag->width - flag->precision - negative) + write(1, "-", 1) + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len));
			return (putchar_nbyte(' ', flag->width - flag->precision - negative) + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len));
		}
		if (flag->plus == TRUE && negative == FALSE)
			return (write(1, "+", 1) + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len));
		if (flag->space == TRUE && negative == FALSE)
			return (write(1, " ", 1) + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len));
		if (negative == TRUE)
			return (write(1, "-", 1) + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len));
		return (putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len));
	}
	
			
	if (flag->width > len)
	{
		if (flag->dash == TRUE)
		{
			if (negative == FALSE && flag->plus == TRUE)
				return (write(1, "+", 1) + putstr_nbyte(str, len) + putchar_nbyte(' ', flag->width - len - 1));
			if (negative == FALSE && flag->space == TRUE)
				return (write(1, " ", 1) + putstr_nbyte(str, len) + putchar_nbyte(' ', flag->width - len - 1));
			if (negative == TRUE)
				return (write(1, "-", 1) + putstr_nbyte(str, len) + putchar_nbyte(' ', flag->width - len));
			return (putstr_nbyte(str, len) + putchar_nbyte(' ', flag->width - len));
		}
		if (flag->zero == TRUE)
		{
			if (negative == FALSE && flag->plus == TRUE)
				return (write(1, "+", 1) + putchar_nbyte('0', flag->width - len - 1) + putstr_nbyte(str, len));
			if (negative == FALSE && flag->space == TRUE)
				return (write(1, " ", 1) +  putchar_nbyte('0', flag->width - len - 1) + putstr_nbyte(str, len));
			if (negative == TRUE)
				return (write(1, "-", 1) + putchar_nbyte('0', flag->width - len - 1) + putstr_nbyte(str, len));
			return (putchar_nbyte('0', flag->width - len) + putstr_nbyte(str, len));
		}
		if (negative == FALSE && flag->plus == TRUE)
			return (write(1, "+", 1) + putchar_nbyte(' ', flag->width - len - 1) + putstr_nbyte(str, len));
		if (negative == TRUE)
			return (putchar_nbyte(' ', flag->width - len) + write(1, "-", 1) + putstr_nbyte(str, len));
		return (putchar_nbyte(' ', flag->width - len) + putstr_nbyte(str, len));
	}
	if (negative == FALSE && flag->plus == TRUE)
		return (write(1, "+", 1) + putstr_nbyte(str, len));
	if (negative == FALSE && flag->space == TRUE)
		return (write(1, " ", 1) + putstr_nbyte(str, len));
	if (negative == TRUE)
		return (write(1, "-", 1) + putstr_nbyte(str, len));
	return (putstr_nbyte(str, len));
}
