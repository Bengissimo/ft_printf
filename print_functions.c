/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:07:09 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/22 17:16:55 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*static void	check_print(t_flag *flag) //to be deleted just for checking
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
	if (flag->prec > 0)
		printf(".%ju", flag->prec);
	printf("len[0]: %c, len[1]: %c", flag->len[0], flag->len[1]);
	fflush(stdout);
	printf(":\n");
	//printf("flag->str: %s\n", flag->str);
}*/

void	fill(t_flag *flag)
{
	fill_specifier(flag);
	if (ft_strlen(flag->str) > 1)
	{
		fill_width(flag);
		fill_flags(flag); //to do change the name
		fill_len_mod(flag, 'h');
		fill_len_mod(flag, 'l');
		fill_len_mod(flag, 'L');
	}
	if (ft_strlen(flag->str) > 1)
		fill_precision(flag);
}

int	put_format(t_flag *flag, va_list ap)
{
	fill(flag);
	//check_print(flag); //to be deleted
	//printf("flag->str: %s\n", flag->str);
	if (flag->spec == 'c')
		return (print_c(flag, ap));
	else if (flag->spec == 's')
		return (print_s(flag, ap));
	else if (flag->spec == 'd' || flag->spec == 'i')
		return (print_signed_int(flag, ap));
	else if (is_char_in_str(flag->spec, UINT) == TRUE)
		return (print_unsigned_int(flag, ap));
	else if (flag->spec == 'f')
		return (print_double(flag, ap)); //TO DO change double name to float
	else if (flag->spec == '%')
		return (handle_char(flag, '%'));
	return (0); //to be deleted
}

int	handle_char(t_flag *flag, char c)
{
	if (flag->width < 1)
		return (write(1, &c, 1));
	if (flag->dash == TRUE)
		return (write(1, &c, 1) + putchar_nbyte(' ', flag->width - 1));
	return (putchar_nbyte(' ', flag->width - 1) + write(1, &c, 1));
}

int	print_c(t_flag *flag, va_list ap)
{
	char	c;

	c = va_arg(ap, int);
	return (handle_char(flag, c));
}

int	print_s(t_flag *flag, va_list ap)
{
	char		*s;
	uintmax_t	len;

	s = va_arg(ap, char *);
	len = ft_strlen(s);
	if (flag->prec > 0 && flag->prec > len)
		len = flag->prec;
	if (flag->width <= len)
		return (putstr_nbyte(s, len));
	if (flag->dash == TRUE) // width > len
		return (putstr_nbyte(s, len) + putchar_nbyte(' ', flag->width - len));
	return (putchar_nbyte(' ', flag->width - len) + putstr_nbyte(s, len));
}
