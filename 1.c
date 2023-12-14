#include "shell.h"

/**
 * reciprocative - checks interactive mode
 * @data: struct used
 *
 * Return: 1 if interactive, or 0
 */
int reciprocative(data_t *data)
{
	return (isatty(STDIN_FILENO) && data->rdfd <= 2);
}

/**
 * delim - checks if character is a delimeter
 * @c: the char to check
 * @dlm: the delimeter string
 * Return: 1 or 0
 */
int delim(char c, char *dlm)
{
	while (*dlm)
		if (*dlm++ == c)
			return (1);
	return (0);
}

/**
 * _lph - checks for alphabetic character
 * @c: The character to input
 * Return: 1 or 0 
 */

int _lph(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _cnvrt - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 or resulted number 
 */

int _cnvrt(char *s)
{
	int i, sgn = 1, flg = 0, tpt;
	unsigned int rslt = 0;

	for (i = 0; s[i] != '\0' && flg != 2; i++)
	{
		if (s[i] == '-')
			sgn *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flg = 1;
			rslt *= 10;
			rslt += (s[i] - '0');
		}
		else if (flg == 1)
			flg = 2;
	}

	if (sgn == -1)
		tpt = -rslt;
	else
		tpt = rslt;

	return (tpt);
}
