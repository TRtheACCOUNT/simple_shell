#include "shell.h"

/**
 * _owneputs – gives input string
 * @str: string
 * Return: Nothing
 */
void _owneputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_owneputchar(str[i]);
		i++;
	}
}

/**
 * _owneputchar - write to stderr
 * @c: The character to print
 *
 * Return: 1 or -1
 */
int _owneputchar(char c)
{
	static int i;
	static char buf[1024];

	if (c == -1 || i >= 1024)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != -1)
		buf[i++] = c;
	return (1);
}

/**
 * _ownputfd - writes to fd
 * @c: The character to print
 * @fd: The file descriptor to write to
 * Return: 1 or -1 or error
 */
int _ownputfd(char c, int fd)
{
	static int i;
	static char buf[1024];

	if (c == -1 || i >= 1024)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != -1)
		buf[i++] = c;
	return (1);
}

/**
 * _ownputsfd - gives an input string
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: number of chars 
 */
int _ownputsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += _ownputfd(*str++, fd);
	}
	return (i);
}
