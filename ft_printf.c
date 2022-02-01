/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 13:51:31 by bkandemi          #+#    #+#             */
/*   Updated: 2022/02/01 11:22:43 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	arg_count(const char *format)
{
	int	count;
	
	count = 0;

	while (*format != '\0')
	{
		if (*format == '%')
			count ++;
		format++;
	}
	return (count);	
}

int	ft_printf(const char *format, ...)
{
	va_list args;
	
	va_start(args, format);
	ft_putnbr(arg_count(format));
	ft_putchar('\n');
	
	va_end(args);
	return (0);
}
