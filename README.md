# ft_printf
Recoding printf function from the standard C library.

## Description
This is the first project of the algorithms branch of Hive Helsinki coding school.
Allowed funcitons to use: write, malloc, free, exit and functions of stdarg.
The prototype is:
```
int  ft_printf(char *format, ...)
```
Each conversion specification is introduced by the character % like this:
```
%[flags][width][.precision][length]specifier
```
For this project my main reference was [International Standard ISO/IEC 9899](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf)

## Usage
- Clone the repo
```
git clone git@github.com:Bengissimo/ft_printf.git
```
- Example use:
```
#include "ft_printf.h"
#include <stdio.h>

int main(void)
{
	ft_printf("%.10f", -0.47560392166578300);
	printf(" <- ft_printf\n");
	printf("%.10f",  -0.47560392166578300);
	printf(" <- original\n\n");
	return (0);
}
```
- Compile and run
```
make -C ./libft/ fclean && make -C ./libft/
make -C ./ fclean && make -C ./
gcc -Wall -Wextra -I./ -L./ -L./libft -lft -lftprintf example.c
make -C ./libft/ fclean && make -C ./ fclean
./a.out
```
- Output:
```
-0.4756039217 <- ft_printf
-0.4756039217 <- original
```

## Test
```
cd test/
./test
```



