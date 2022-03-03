/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:40:33 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/03 10:40:32 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

/* original printf result is in parenthesis */
void	test_int(char *format, int nb)
{
	ft_printf(format, nb);
	printf("(");
	printf(format, nb);
	printf(")\n\n");
}

int main(void)
{
	//long pos = 0;
	//int neg = -8;

	printf("test for positive integer:\n");

	/*test_int("%d", pos);
	test_int("%-d", pos);
	test_int("%+d", pos);
	test_int("% d", pos);
	test_int("%---d", pos);
	test_int("%+++d", pos);
	test_int("%   d", pos);
	test_int("%-+d", pos);
	test_int("%- d", pos);
	test_int("%5d", pos);
	test_int("%+5d", pos);
	test_int("%-5d", pos);
	test_int("%-+5d", pos);
	test_int("%- 5d", pos);
	test_int("%.3d", pos);
	test_int("%-.3d", pos);
	test_int("%-+.3d", pos);
	test_int("%- .3d", pos);
	test_int("%5.3d", pos);
	test_int("%-5.3d", pos);
	test_int("%-+5.3d", pos);
	test_int("%- 5.3d", pos);
	test_int("% 6.3d", pos);
	test_int("%+6.3d", pos);
	test_int("%05d", pos);
	test_int("%0+5d", pos);
	test_int("% 05d", pos);*/
	test_int("%.0d", 0);
	/*test_int("%hd", pos);
	test_int("%ld", pos);
	test_int("%lld", pos);*/

	printf("test for negative integer:\n");

	/*test_int("%d", neg);
	test_int("%-d", neg);
	test_int("%+d", neg);
	test_int("% d", neg);
	test_int("%---d", neg);
	test_int("%+++d", neg);
	test_int("%   d", neg);
	test_int("%-+d", neg);
	test_int("%- d", neg);
	test_int("%5d", neg);
	test_int("%+5d", neg);
	test_int("%-5d", neg);
	test_int("%-+5d", neg);
	test_int("%- 5d", neg);
	test_int("%.3d", neg);
	test_int("%-.3d", neg);
	test_int("%-+.3d", neg);
	test_int("%- .3d", neg);
	test_int("%6.3d", neg);
	test_int("%-6.3d", neg);
	test_int("%-+6.3d", neg);
	test_int("%- 6.3d", neg);
	test_int("% 6.3d", neg);
	test_int("%+6.3d", neg);
	test_int("%05d", neg);
	test_int("%0+5d", neg);
	test_int("% 05d", neg);*/
	
	return (0);
}


/*
for d or i
.  if precision > strlen, add leading (precision - strlen) zeros {
		if width > (precision) and no dash_flag, add (width - precision - strlen) leading space  
		if there is dash_flag add (width - precision - strlen) trailing space}
	else if precision <= strlen, print str.



*/