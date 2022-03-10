/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 10:36:08 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/10 11:30:46 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char *dtoa(long double nb)
{
	int exp;
	int len_first;
	int len_second;
	char *str1;
	char *str2;

	if (nb < 0)
		nb = -nb;
	exp = 0;
	while ((int)(nb * 10) % 10)
	{
		nb *= 10;
		exp++;
	}
	len_first = intlen((int)nb);
	str1 = ft_itoa_base((uintmax_t)nb, 10);
	
	
	
	
		
}