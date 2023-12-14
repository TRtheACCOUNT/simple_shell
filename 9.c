#include "shell.h"

/**
 * gt_nvron - gives the environ. 
 * @data: Struct containing arguments.
 * Return: 0
 */
char **gt_nvrn(data_t *data)
{
	if (!data->environ || data->env_changed)
	{
		data->environ = list_to_strings(data->env);
		data->env_changed = 0;
	}

	return (data->environ);
}

/**
 * _owunsetenv - deletes an environment variable
 * @data: Structure containing arguments.
 *  Return: 1 or 0
 * @var: the string env var property
 */
int _owunsetenv(data_t *data, char *var)
{
	list_t *node = data->env;
	size_t i = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = ownstarts_with(node->str, var);
		if (p && *p == '=')
		{
			data->env_changed = dlt_nd_ndx(&(data->env), i);
			i = 0;
			node = data->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (data->env_changed);
}

/**
 * _stenv - Initialize or modify a variable
 * @info: Struct containing arguments
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
 */
int _stenv(data_t *data, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_ownstrlen(var) + _ownstrlen(value) + 2);
	if (!buf)
		return (1);
	_ownstrcpy(buf, var);
	_ownstrcat(buf, "=");
	_ownstrcat(buf, value);
	node = data->env;
	while (node)
	{
		p = ownstarts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			data->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	dd_nd_nd(&(data->env), buf, 0);
	free(buf);
	data->env_changed = 1;
	return (0);
}
