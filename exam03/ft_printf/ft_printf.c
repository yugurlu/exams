
#include <stdarg.h>
#include <unistd.h>

int putchar(char s)
{
	return(write(1, &s, 1));
}

int printstr(char *s)
{
	int i = 0;
	int result = 0;

	if(!s)
		return(write(1, "(null)", 6));
	while (s[i])
		result += putchar(s[i++]);
	return(result);
}

int printnumber(unsigned int number, int base)
{
	int result = 0;
	int i = number % base;
	char *basee = "0123456789abcdef";

	if (number / base > 0)
		result += printnumber(number / base, base);
	result += putchar(basee[i]);
	return (result);
}

int printd(int number)
{
	int result = 0;
	if (number < 0)
	{
		if (number == -2147483648)
			return(write(1, "-2147483648", 11));
		result += putchar('-');
		number *= -1;
	}
	result += printnumber((unsigned int)number, 10);
	return (result);
}

int ft_printf(char *start, ...)
{
	int i = 0;
	int result = 0;
	va_list ap;

	if(!start)
		return (0);
	va_start(ap, start);
	while (start[i])
	{
		if(start[i] == '%')
		{
			if (start[i + 1] == 's')
				result += printstr(va_arg(ap, char *));
			else if (start[i + 1] == 'd')
				result += printd(va_arg(ap, int));
			else if (start[i + 1] == 'x')
				result += printnumber(va_arg(ap, unsigned int), 16);
			i++;
		}
		else
			result += putchar(start[i]);
		i++;
	}
	va_end(ap);
	return(result);
}
