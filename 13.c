#include "shell.h"

/**
 * lst_ln - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t lst_ln(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * lst_t_strngs - gives an array of strings
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **lst_t_strngs(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_ownstrlen(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _ownstrcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * prnt_lst - gives elements of a linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t prnt_lst(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_ownputs(convert_number(h->num, 10, 0));
		_ownputchar(':');
		_ownputchar(' ');
		_ownputs(h->str ? h->str : "(nil)");
		_ownputs("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * nd_strts_wth - returns node whith a certain biggening
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *nd_strts_wth(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = ownstarts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * gt_nd_ndx - gives the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index or -1
 */
ssize_t gt_nd_ndx(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
