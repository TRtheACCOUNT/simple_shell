#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 or -1
 */
int main(int ac, char **av)
{
	data_t data[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_owneputs(av[0]);
				_owneputs(": 0: Can't open ");
				_owneputs(av[1]);
				_owneputchar('\n');
				_owneputchar(-1);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		data->rdfd = fd;
	}
	pplt_env_lst(data);
	rd_hstry(data);
	hsh(data, av);
	return (EXIT_SUCCESS);
}
#include "shell.h"

/**
 * bfr - frees a pointer and give NULL to adress
 * @ptr: address of the pointer to free
 * Return: 1 or 0
 */
int bfr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
