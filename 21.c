#include "shell.h"

/**
 * chain - test if current char in buffer is a chain delimeter
 * @data: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 or 0
 */
int chain(data_t *data, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		data->cmd_buf_type = 1;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		data->cmd_buf_type = 2;
	}
	else if (buf[j] == ';') 
	{
		buf[j] = 0; 
		data->cmd_buf_type = 3;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @data: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(data_t *data, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (data->cmd_buf_type == CMD_AND)
	{
		if (data->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (data->cmd_buf_type == CMD_OR)
	{
		if (!data->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(data_t *data)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = nd_strts_wth(data->alias, data->argv[0], '=');
		if (!node)
			return (0);
		free(data->argv[0]);
		p = _ownstrchr(node->str, '=');
		if (!p)
			return (0);
		p = _ownstrdup(p + 1);
		if (!p)
			return (0);
		data->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * @data: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(data_t *data)
{
	int i = 0;
	list_t *node;

	for (i = 0; data->argv[i]; i++)
	{
		if (data->argv[i][0] != '$' || !data->argv[i][1])
			continue;

		if (!_ownstrcmp(data->argv[i], "$?"))
		{
			replace_string(&(data->argv[i]),
					_ownstrdup(cnvrt_nmbr(data->status, 10, 0)));
			continue;
		}
		if (!_ownstrcmp(data->argv[i], "$$"))
		{
			replace_string(&(data->argv[i]),
					_ownstrdup(cnvrt_nmbr(getpid(), 10, 0)));
			continue;
		}
		node = nd_strts_wth(data->env, &data->argv[i][1], '=');
		if (node)
		{
			replace_string(&(data->argv[i]),
					_ownstrdup(_ownstrchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&data->argv[i], _ownstrdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
