/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gather_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:49:24 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/26 21:35:47 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	calc_width_asterix(t_flag *flag, int width)
{
	if (width < 0)
	{
		flag->dash = TRUE;
		flag->zero = FALSE;
		return (-width);
	}
	return (width);
}

int	gather_width(t_flag *flag, va_list ap)
{
	int		i;
	long	width;

	i = 0;
	while (is_char_in_str(flag->str[i], FLAGS) == TRUE && flag->str[i] != '\0')
		i++;
	if (flag->str[i] == '*')
	{
		width = va_arg(ap, int);
		if (ft_isdigit(flag->str[i + 1]) == TRUE)
			i++;
		else
			return (calc_width_asterix(flag, width));
	}
	width = 0;
	while (flag->str[i] != '\0' && ft_isdigit(flag->str[i]) == TRUE)
	{
		width = width * 10 + flag->str[i] - '0';
		if (width > 2147483644)
			return (-1);
		i++;
	}
	if (flag->width < 0)
		flag->zero = FALSE;
	return (width);
}
