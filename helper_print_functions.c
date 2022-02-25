/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_print_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:11:19 by bkandemi          #+#    #+#             */
/*   Updated: 2022/02/25 11:16:53 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_repeated(char c, int count)
{
	int	i = 0;

	while (i < count)
	{
		write(1, &c, 1);
		i++;
	}
	return (count);
}

int	putstr_nbyte(char const *s, int nbyte)
{
	return (write(1, s, nbyte));
}
