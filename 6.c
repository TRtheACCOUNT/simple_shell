#include "shell.h"

/**
 * _cnvrtnt - turns a string to an integer
 * @s: the string to be converted
 * Return: 0 or -1
 */
int _cnvrtnt(char *s)
{
	int i = 0;
	unsigned long int rslt = 0;

	if (*s == '+')
		s++; 
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			rslt *= 10;
			rslt += (s[i] - '0');
			if (rslt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rslt);
}

/**
 * puts_error - gives an error message
 * @data: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 or -1
 */
void puts_error(data_t *data, char *estr)
{
	_owneputs(data->fname);
	_owneputs(": ");
	ownputs_d(data->line_count, STDERR_FILENO);
	_owneputs(": ");
	_owneputs(data->argv[0]);
	_owneputs(": ");
	_owneputs(estr);
}

/**
 * ownputs_d – gives a number of base 10
 * @npt: the input
 * @fd: the file descriptor to write to
 *
 * Return: how many numbers printed
 */
int ownputs_d(int npt, int fd)
{
	int (*__putchar)(char) = _ownputchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _owneputchar;
	if (npt < 0)
	{
		_abs_ = -npt;
		__putchar('-');
		count++;
	}
	else
		_abs_ = npt;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * cnvrt_nmbr - converte
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *cnvrt_nmbr(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rmv_cmnts - replace '#' with '\0'
 * @buf: address of what to replace
 *
 * Return: 0;
 */
void rmv_cmnts(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
