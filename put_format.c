/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:54:03 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/26 21:35:00 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill(t_flag *flag, va_list ap)
{
	gather_specifier(flag);
	if (ft_strlen(flag->str) > 1)
	{
		gather_flags(flag);
		flag->width = gather_width(flag, ap);
		flag->prec = gather_precision(flag, ap);
		gather_len_mod(flag, 'h');
		gather_len_mod(flag, 'l');
		gather_len_mod(flag, 'L');
	}
}

int	put_format(t_flag *flag, va_list ap)
{
	fill(flag, ap);
	if (flag->spec == 'c')
		return (print_char(flag, ap));
	else if (flag->spec == 's')
		return (print_str(flag, ap));
	else if (flag->spec == 'd' || flag->spec == 'i')
		return (print_signed_int(flag, ap));
	else if (is_char_in_str(flag->spec, UINT) == TRUE)
		return (print_unsigned_int(flag, ap));
	else if (flag->spec == 'f')
		return (print_float(flag, ap));
	else if (flag->spec == '%')
		return (handle_char(flag, '%'));
	else
		exit(1);
}
