#include "shell.h"

/**
 * _ownhistory - gives the history 
 * @data: Struct containing arguments.
 *  Return: 0
 */
int _ownhistory(data_t *data)
{
	prnt_lst(data->history);
	return (0);
}

/**
 * cnvrt_alias - convert alias to string
 * @data: struct
 * @str: the alias
 *
 * Return: 0 or 1.
 */
int cnvrt_alias(data_t *data, char *str)
{
	char *p, c;
	int ret;

	p = own_strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = dlt_nd_ndx(&(data->alias),
		gt_nd_ndx(data->alias, nd_strts_wth(data->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * st_alias - sets alias to string
 * @data: parameter struct
 * @str: the string alias
 *
 * Return: 0 or 1 
 */
int st_alias(data_t *data, char *str)
{
	char *p;

	p = own_strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (cnvrt_alias(data, str));

	cnvrt_alias(data, str);
	return (dd_nd_nd(&(data->alias), str, 0) == NULL);
}

/**
 * puts_alias – gives the string
 * @nd: the alias node
 *
 * Return: 0 or 1
 */
int puts_alias(list_t *nd)
{
	char *p = NULL, *a = NULL;

	if (nd)
	{
		p = _ownstrchr(nd->str, '=');
		for (a = nd->str; a <= p; a++)
		own_putchar(*a);
		own_putchar('\'');
		own_puts(p + 1);
		own_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _ownalias – acts like the builtin
 * @data: Struct containing arguments.
 *  Return: 0
 */
int _ownalias(data_t *data)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (data->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			puts_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; data->argv[i]; i++)
	{
		p = _ownstrchr(data->argv[i], '=');
		if (p)
			st_alias(data, data->argv[i]);
		else
			puts_alias(nd_strts_wth(data->alias, data->argv[i], '='));
	}

	return (0);
}
