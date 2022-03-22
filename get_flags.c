/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:28:55 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/22 17:07:22 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill_specifier(t_flag *flag)
{
	char	*end;
	int		i;

	i = 0;
	end = ft_strchr(flag->str, '\0');
	while (SPECS[i] != '\0')
	{
		if (*(end - 1) == SPECS[i])
			flag->spec = SPECS[i];
		i++;
	}
}

void	fill_flags(t_flag *flag)
{
	int	i;

	i = 0;
	while (flag->str[i] != '\0' && is_char_in_str(flag->str[i], FLAGS) == TRUE)
	{
		if (flag->str[i] == '-')
			flag->dash = TRUE;
		else if (flag->str[i] == '+')
			flag->plus = TRUE;
		else if (flag->str[i] == '#')
			flag->hash = TRUE;
		else if (flag->str[i] == ' ' && flag->plus == FALSE)
			flag->space = TRUE;
		else if (flag->str[i] == '0' && flag->width > 0 && flag->dash == FALSE)
			flag->zero = TRUE;
		i++;
	}
}

void	fill_width(t_flag *flag)
{
	int		i;
	long	width;

	i = 0;
	width = 0;
	while (is_char_in_str(flag->str[i], FLAGS) == TRUE && flag->str[i] != '\0')
		i++;
	while (flag->str[i] != '\0' && ft_isdigit(flag->str[i]) == TRUE)
	{
		width = width * 10 + flag->str[i] - '0';
		if (width > 2147483644)
		{
			width = -1;
			break ;
		}
		i++;
	}
	flag->width = width;
}

void	fill_precision(t_flag *flag)
{
	char	*dot;
	long	precision;
	int		i;

	precision = 0;
	i = 1;
	dot = ft_strchr(flag->str, '.');
	if (dot != NULL)
		flag->dot = TRUE;
	while (dot != NULL && dot[i] != '\0' && ft_isdigit(dot[i]) == TRUE)
	{
		precision = precision * 10 + dot[i] - '0';
		if (precision > 2147483646)
		{
			precision = -1;
			break ;
		}
		i++;
	}
	flag->prec = precision;
}

void	fill_len_mod(t_flag *flag, char c)
{
	char	*len_flag;

	len_flag = ft_strchr(flag->str, c);
	if (len_flag != NULL)
	{
		if (*(len_flag + 2) == '\0')
		{
			flag->len[0] = c;
			return ;
		}
		if (*(len_flag + 1) == c && *(len_flag + 3) == '\0')
		{
			flag->len[0] = c;
			flag->len[1] = c;
			return ;
		}
		if (len_flag != NULL && (*(len_flag + 1)) == 'f')
		{
			flag->len[0] = c;
			return ;
		}
	}
}
