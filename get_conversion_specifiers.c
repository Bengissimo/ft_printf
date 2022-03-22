/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_conversion_specifiers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:28:55 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/22 11:24:43 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void fill_specifier(t_flag *flag)
{
	char	*end;
	int	i;

	i = 0;
	end = ft_strchr(flag->str, '\0');
	while (SPECS[i] != '\0')
	{
		if (*(end - 1) == SPECS[i])
			flag->spec = SPECS[i];
		i++;
	}
}

static void	fill_flags(t_flag *flag)
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

static void fill_width(t_flag *flag)
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
			break;
		}
		i++;
	}
	flag->width = width;
}

static void	fill_precision(t_flag *flag)
{
	char	*dot;
	long	precision;
	int		i;

	precision = 0;
	i = 1;
	dot = ft_strchr(flag->str, '.');
	while (dot != NULL && dot[i] != '\0' && ft_isdigit(dot[i]) == TRUE)
	{
		
		flag->dot = TRUE;
		precision = precision * 10 + dot[i] - '0';
		if (precision > 2147483646)
		{
			precision = -1;
			break;
		}
		i++;
	}
	flag->prec = precision;
}

static int	fill_length_h(t_flag *flag)
{
	char	*h;

	h = ft_strchr(flag->str, 'h');
	if (h != NULL)
	{
		if (is_char_in_str(*(h + 1), INT) == TRUE && *(h + 2) == '\0')
		{
			flag->length[0] = 'h';
			return (TRUE);
		}
		if (*(h + 1) == 'h' && is_char_in_str(*(h + 1), INT) == TRUE && *(h + 3) == '\0')
		{
			flag->length[0] = 'h';
			flag->length[1] = 'h';
			return (TRUE);
		}
	}
	return (FALSE);
}

static int	fill_length_l(t_flag *flag)
{
	char	*lower_l;

	lower_l = ft_strchr(flag->str, 'l');
	if (lower_l != NULL)
	{
		if (is_char_in_str(*(lower_l + 1), INT) == TRUE && *(lower_l + 2) == '\0')
		{
			flag->length[0] = 'l';
			return (TRUE);
		}
		if (*(lower_l + 1) == 'l' && is_char_in_str(*(lower_l + 1), INT) == TRUE && *(lower_l + 3) == '\0')
		{
			flag->length[0] = 'l';
			flag->length[1] = 'l';
			return (TRUE);
		}
	}
	return (FALSE);
}

static int	fill_length_upper_l(t_flag *flag)
{
	char	*upper_l;

	upper_l = ft_strchr(flag->str, 'L');
	if (upper_l != NULL && (*(upper_l + 1)) == 'f')
	{
		flag->length[0] = 'L';
		return (TRUE);
	}
	return (FALSE);
}

void	fill(t_flag *flag)
{
	fill_specifier(flag);
	if (ft_strlen(flag->str) > 1)
	{
		fill_width(flag);
		fill_flags(flag); //to do change the name
		fill_length_h(flag);
		fill_length_l(flag);
		fill_length_upper_l(flag);
	}
	if (ft_strlen(flag->str) > 2)
		fill_precision(flag);
}
