/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:40:33 by bkandemi          #+#    #+#             */
/*   Updated: 2022/02/25 14:27:57 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	int nb = -8;
	/*char c = 'c';
	char *str = "abc";*/
	
	ft_printf("1: Hello (%d)\n", nb);
	/* is precision > 0 */
	ft_printf("2: Hello (%.5d)\n", nb);
	ft_printf("3: Hello (%6.5d)\n", nb); // is width > precision
	ft_printf("4: Hello (% 6.5d)\n", nb);
	ft_printf("5: Hello (%+6.5d)\n", nb);
	ft_printf("6: Hello (%-+6.5d)\n", nb);
	ft_printf("7: Hello (%- 6.5d)\n", nb);
	ft_printf("8: Hello (%+.5d)\n", nb);
	ft_printf("9: Hello (%-.5d)\n", nb);
	ft_printf("10: Hello (% .5d)\n", nb);
	ft_printf("11: Hello (%- .5d)\n", nb);
	ft_printf("12: Hello (%-+.5d)\n", nb);

	printf("\n1: Hello (%d)\n", nb);
	/* is precision > 0 */
	printf("2: Hello (%.5d)\n", nb);
	printf("3: Hello (%6.5d)\n", nb); // is width > precision
	printf("4: Hello (% 6.5d)\n", nb);
	printf("5: Hello (%+6.5d)\n", nb);
	printf("6: Hello (%-+6.5d)\n", nb);
	printf("7: Hello (%- 6.5d)\n", nb);
	printf("8: Hello (%+.5d)\n", nb);
	printf("9: Hello (%-.5d)\n", nb);
	printf("10: Hello (% .5d)\n", nb);
	printf("11: Hello (%- .5d)\n", nb);
	printf("12: Hello (%-+.5d)\n", nb);
	return (0);
}


/*
for d or i
.  if precision > strlen, add leading (precision - strlen) zeros {
		if width > (precision) and no dash_flag, add (width - precision - strlen) leading space  
		if there is dash_flag add (width - precision - strlen) trailing space}
	else if precision <= strlen, print str.



*/