#include "shell.h"

/**
 **_ownstrncpy – makes a copy of a string
 *@dst: destination string
 *@src: source string
 *@n: number of characters to make copie
 *Return: the resulted string
 */
char *_ownstrncpy(char *dst, char *src, int n)
{
	int i, j;
	char *s = dst;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dst[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_ownstrncat – merges two strings
 *@dst: string 1 
 *@src: string 2
 *@n: max number of bytes
 *Return: the concatenated string
 */
char *_ownstrncat(char *dst, char *src, int n)
{
	int i, j;
	char *s = dst;

	i = 0;
	j = 0;
	while (dst[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dst[i] = '\0';
	return (s);
}

/**
 **_ownstrchr - locates a character in a string
 *@s: the string 
 *@c: the character 
 *Return: pointer to the memory area 
 */
char *_ownstrchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
