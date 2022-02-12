/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_conversion_specifiers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:28:55 by bkandemi          #+#    #+#             */
/*   Updated: 2022/02/12 23:03:32 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	initiate(t_conv_spec *arg)
{
	ft_bzero(arg->str, 30);
	arg->specifier = '\0';
	arg->dash_flag= FALSE;
	arg->hash_flag= FALSE;
	arg->plus_flag= FALSE;
	arg->space_flag = FALSE;
	arg->zero_flag= FALSE;
	arg->width_int = 0;
	arg->precision = 0;
	ft_bzero(arg->length, 2);
}

static void fill_specifier(t_conv_spec *arg)
{
	char	*end;
	int	i;

	i = 0;
	end = ft_strchr(arg->str, '\0');
	while (CONVERSIONS[i] != '\0')
	{
		if (*(end - 1) == CONVERSIONS[i])
			arg->specifier = CONVERSIONS[i];
		i++;
	}
}

static int	is_char_in_str(char c, char *str)
{
	int	i;
	int found;

	found = FALSE;
	i = 0;
	while (str[i] != '\0')
	{
		if (c == str[i])
		{
			found = TRUE;
			break ;
		}
		i++;
	}
	return (found);
}

static void	fill_flags(t_conv_spec *arg) //flag olmayan birseyle karsilasinca break
{
	int	i;

	i = 0;
	while (arg->str[i] != '\0')
	{
		if (is_char_in_str('-', arg->str) == TRUE)
			arg->dash_flag = TRUE;
		if (is_char_in_str('+', arg->str) == TRUE)
			arg->plus_flag = TRUE;
		if (is_char_in_str('#', arg->str) == TRUE)
			arg->hash_flag = TRUE;
		if (is_char_in_str(' ', arg->str) == TRUE && arg->plus_flag == FALSE)
			arg->space_flag = TRUE;
		if (is_char_in_str('0', arg->str) == TRUE && arg->dash_flag == FALSE
		&& ft_isdigit(arg->str[i + 1]) == TRUE)
			arg->zero_flag = TRUE;
		i++;
	}
}

static int	is_flag(char c)
{
	int i;

	i = 0;
	while (FLAGS[i] != '\0')
	{
		if (c == FLAGS[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static void fill_width(t_conv_spec *arg)
{
	int i;
	int	width;

	i = 0;
	while (is_flag(arg->str[i]) == TRUE && arg->str[i] != '\0')
		i++;
	if (ft_isdigit(arg->str[i + 10]) == FALSE)
	{
		width = ft_atoi(arg->str + i);
		if (width > 0 && width < 2147483647)
			arg->width_int = width;
	}
}

static void	fill_precision(t_conv_spec *arg)
{
	char *dot;

	dot = ft_strchr(arg->str, '.');
	if (dot != NULL && ft_isdigit(*(dot + 1)) == TRUE)
		arg->precision = ft_atoi(dot + 1);
	arg->precision = 0;
	//if there is '-' after '.' ignore prceision!
}

static int	is_int_or_octal(char c)
{
	int	i;

	i = 0;
	while (INT_OR_OCTAL[i] != '\0')
	{
		if (c == INT_OR_OCTAL[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}


static int	fill_length_h(t_conv_spec *arg)
{
	char	*h;

	h = ft_strchr(arg->str, 'h');
	if (h != NULL)
	{
		if (is_int_or_octal(*(h + 1)) == TRUE && *(h + 2) == '\0')
		{
			arg->length[0] = 'h';
			return (TRUE);
		}
		if (*(h + 1) == 'h' && is_int_or_octal(*(h + 2)) == TRUE && *(h + 3) == '\0')
		{
			arg->length[0] = 'h';
			arg->length[1] = 'h';
			return (TRUE);
		}
	}
	return (FALSE);
}

static int	fill_length_l(t_conv_spec *arg)
{
	char	*lower_l;

	lower_l = ft_strchr(arg->str, 'l');
	if (lower_l != NULL)
	{
		if (is_int_or_octal(*(lower_l + 1)) == TRUE && *(lower_l + 2) == '\0')
		{
			arg->length[0] = 'l';
			return (TRUE);
		}
		if (*(lower_l + 1) == 'l' && is_int_or_octal(*(lower_l + 2)) == TRUE && *(lower_l + 3) == '\0')
		{
			arg->length[0] = 'l';
			arg->length[1] = 'l';
			return (TRUE);
		}
	}
	return (FALSE);
}

static int	fill_length_upper_l(t_conv_spec *arg)
{
	char	*upper_l;

	upper_l = ft_strchr(arg->str, 'L');
	if (upper_l != NULL && is_int_or_octal(*(upper_l + 1)) == TRUE)
	{
		arg->length[0] = 'L';
		return (TRUE);
	}
	return (FALSE);
}


void	fill(t_conv_spec *arg)
{
	int	i;

	i = 0;
	while (arg->str[i] != '\0')
	{
		if (is_char_in_str(arg->str[i], VALID_CHARS) == FALSE)
		{
			ft_putendl("invalid format");
			exit(-1);
		}
		i++;
	}
	fill_specifier(arg);
	if (ft_strlen(arg->str) > 1)
	{
		fill_flags(arg);
		fill_width(arg);	
		fill_length_h(arg);
		fill_length_l(arg);
		fill_length_upper_l(arg);
	}
	if (ft_strlen(arg->str) > 2)
		fill_precision(arg);
}