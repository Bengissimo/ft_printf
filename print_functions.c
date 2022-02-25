/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:07:09 by bkandemi          #+#    #+#             */
/*   Updated: 2022/02/25 13:58:09 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*static void	check_print(t_flag *flag)
{
	printf("str: %s\n", flag->str);
	printf("dash: %d, hash: %d, plus: %d, space: %d, zero: %d\n", flag->dash, flag->hash, flag->plus, flag->space, flag->zero);
	printf("width: %d\n", flag->width);
	printf("precision: %d\n", flag->precision);
	printf("length[0]: %c, length[1]: %c\n", flag->length[0], flag->length[1]);
	printf("specifier: %c\n", flag->specifier);
}*/

/*static void	put_fmt_nbr(int nb)
{
	ft_putnbr(nb);
}*/


void	put_format(t_flag *flag, va_list ap)
{
	fill(flag);
	//check_print(flag);
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
	
	nb = va_arg(ap, int);
	str = ft_itoa(nb);
	len  = ft_strlen(str);
	if (flag->precision > 0 && flag->precision > len) //if precision true ignore 0 flag
	{
		if (flag->width > flag->precision)
		{
			if (flag->dash == TRUE)
			{
				if (flag->plus == TRUE && str[0] != '-')
					return (write(1, "+", 1) + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len) + putchar_nbyte(' ', flag->width - flag->precision));
				if (flag->space == TRUE && str[0] != '-')
					return (write(1, " ", 1) + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len) + putchar_nbyte(' ', flag->width - flag->precision));
				return (putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len) + putchar_nbyte(' ', flag->width - flag->precision));
			}
			if (flag->plus == TRUE && str[0] != '-')
				return (putchar_nbyte(' ', flag->width - flag->precision -1) + write(1, "+", 1) + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len));
			if (flag->space == TRUE && str[0] != '-')
				return (putchar_nbyte(' ', flag->width - flag->precision -1) + write(1, " ", 1) + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len));
			return (putchar_nbyte(' ', flag->width - flag->precision) + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len));
		}
		if (flag->dash == TRUE)
			return (putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len));
		if (flag->plus == TRUE && str[0] != '-')
				return (write(1, "+", 1) + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len));
		if (flag->space == TRUE && str[0] != '-')
				return (write(1, " ", 1) + putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len));
		return (putchar_nbyte('0', flag->precision - len) + putstr_nbyte(str, len));
	}
	if (flag->width > len)
	{
		if (flag->dash == TRUE)
		{
			if (str[0] != '-' && flag->plus == TRUE)
				return (write(1, "+", 1) + putstr_nbyte(str, len) + putchar_nbyte(' ', flag->width - len - 1));
			if (str[0] != '-' && flag->space == TRUE)
				return (write(1, " ", 1) + putstr_nbyte(str, len) + putchar_nbyte(' ', flag->width - len - 1));
			return (putstr_nbyte(str, len) + putchar_nbyte(' ', flag->width - len));
		}
		if (flag->zero == TRUE)
		{
			if (str[0] != '-' && flag->plus == TRUE)
				return (write(1, "+", 1) + putchar_nbyte('0', flag->width - len - 1) + putstr_nbyte(str, len));
			if (str[0] != '-' && flag->space == TRUE)
				return (write(1, " ", 1) +  putchar_nbyte('0', flag->width - len - 1) + putstr_nbyte(str, len));
			return (putchar_nbyte('0', flag->width - len) + putstr_nbyte(str, len));
		}
		if (str[0] != '-' && flag->plus == TRUE)
			return (write(1, "+", 1) + putchar_nbyte(' ', flag->width - len - 1) + putstr_nbyte(str, len));
		return (putchar_nbyte(' ', flag->width - len) + putstr_nbyte(str, len));
	}
	if (str[0] != '-' && flag->plus == TRUE)
		return (write(1, "+", 1) + putstr_nbyte(str, len));
	if (str[0] != '-' && flag->space == TRUE)
		return (write(1, " ", 1) + putstr_nbyte(str, len));
	return (putstr_nbyte(str, len));
}
