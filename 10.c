#include "shell.h"

/**
 * clr_data - initializes data_t struct
 * @data: struct address
 */
void clr_data(data_t *data)
{
	data->arg = NULL;
	data->argv = NULL;
	data->path = NULL;
	data->argc = 0;
}

/**
 * st_data - initializes data_t struct
 * @data: struct address
 * @av: argument vector
 */
void st_data(data_t *data, char **av)
{
	int i = 0;

	data->fname = av[0];
	if (data->arg)
	{
		data->argv = strtok(data->arg, " \t");
		if (!data->argv)
		{
			data->argv = malloc(sizeof(char *) * 2);
			if (data->argv)
			{
				data->argv[0] = _ownstrdup(data->arg);
				data->argv[1] = NULL;
			}
		}
		for (i = 0; data->argv && data->argv[i]; i++)
			;
		data->argc = i;

		replace_alias(data);
		replace_vars(data);
	}
}

/**
 * fr_data - frees data_t struct fields
 * @data: struct address
 * @all: true if freeing all fields
 */
void fr_data(data_t *data, int all)
{
	ffr(data->argv);
	data->argv = NULL;
	data->path = NULL;
	if (all)
	{
		if (!data->cmd_buf)
			free(data->arg);
		if (data->env)
			fr_lst(&(data->env));
		if (data->history)
			fr_lst(&(data->history));
		if (data->alias)
			fr_lst(&(data->alias));
		ffr(data->environ);
			data->environ = NULL;
		free((void **)data->cmd_buf);
		if (data->rdfd > 2)
			close(data->rdfd);
		_ownputchar(-1);
	}
}
