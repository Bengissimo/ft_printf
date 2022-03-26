/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:28:55 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/26 21:31:19 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	gather_specifier(t_flag *flag)
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

void	gather_flags(t_flag *flag)
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
		else if (flag->str[i] == '0')
			flag->zero = TRUE;
		i++;
	}
	if (flag->dash == TRUE)
		flag->zero = FALSE;
}

void	gather_len_mod(t_flag *flag, char c)
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
