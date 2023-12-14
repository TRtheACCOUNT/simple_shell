
#include "shell.h"

/**
 * _ownenv - gives the environment
 * @data: Struct containing arguments.
 * Return: 0
 */
int _ownenv(data_t *data)
{
	prnt_lst_str(data->env);
	return (0);
}

/**
 * _gtenv - gives the environ variable
 * @data: Struct containing arguments.
 * @name: env var name
 *
 * Return: the variable
 */
char *_gtenv(data_t *data, const char *name)
{
	list_t *node = data->env;
	char *p;

	while (node)
	{
		p = ownstarts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _ownstenv - Start a variable or intiates one
 * @data: Struct containing arguments.
 *  Return: 0
 */
int _ownstenv(data_t *data)
{
	if (data->argc != 3)
	{
		_owneputs("false number of arguements\n");
		return (1);
	}
	if (_stenv(data, data->argv[1], data->argv[2]))
		return (0);
	return (1);
}

/**
 * _ownunstenv - delete an environment variable
 * @data: Struct containing arguments.
 * Return: 0
 */
int _ownunstenv(data_t *data)
{
	int i;

	if (data->argc == 1)
	{
		_owneputs("low number of arguements.\n");
		return (1);
	}
	for (i = 1; i <= data->argc; i++)
		_owneputs (data, data->argv[i]);

	return (0);
}

/**
 * pplt_env_list - populates env linked list
 * @data: Struct containing arguments.
 * Return: Always 0
 */
int pplt_env_list(data_t *data)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		dd_nd_nd(&node, environ[i], 0);
	data->env = node;
	return (0);
}
