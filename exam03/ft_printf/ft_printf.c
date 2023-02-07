
#include <unistd.h>
#include <stdarg.h>

int putchar(char s)
{
	return(write(1, &s, 1));
}

int printstr(char *str)
{
	int i = 0;
	int result = 0;
	if(!str)
		return (write(1, "(null)", 6));
	while (str[i])
		result += putchar(str[i++]);
	return (result);
}

int putnumber(unsigned int number, int base)
{
	int result = 0;
	int i = number % base;
	char *basee = "0123456789abcdef";

	if (number / base > 0)
		result += putnumber(number / base, base);
	result += putchar(basee[i]);
	return (result);
}

int printd(int number)
{
	int result = 0;
	if (number < 0)
	{
		if (number == -2147483648)
			return (write(1, "-2147483648", 11));
		result += putchar('-');
		number *= -1;
	}
	result += putnumber((unsigned int)number, 10);
	return (result);
}

int ft_printf(char *str, ...)
{
	int i = 0;
	int result = 0;
	va_list ap;

	if(!str)
		return (0);
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == 's')
				result += printstr(va_arg(ap, char *));
			else if (str[i + 1] == 'd')
				result += printd(va_arg(ap, int));
			else if (str[i + 1] == 'x')
				result += putnumber(va_arg(ap, unsigned int), 16);
			i++;
		}
		else
			result += putchar(str[i]);
		i++;
	}
	va_end(ap);
	return (result);
}
