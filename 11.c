#include "shell.h"

/**
 * gt_hstry_fl - gets the history file
 * @data: parameter struct
 *
 * Return: history of file
 */

char *gt_hstry_fl(data_t *data)
{
	char *buf, *dir;

	dir = _gtenv(data, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_ownstrlen(dir) + _ownstrlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_ownstrcpy(buf, dir);
	_ownstrcat(buf, "/");
	_ownstrcat(buf, HIST_FILE);
	return (buf);
}

/**
 * wrt_hstry – create a file
 * @info: struct
* Return: 1 or -1
 */
int wrt_hstry(data_t *data)
{
	ssize_t fd;
	char *filename = gt_hstry_fl(data);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = data->history; node; node = node->next)
	{
		_ownputsfd(node->str, fd);
		_ownputfd('\n', fd);
	}
	_ownputfd(-1, fd);
	close(fd);
	return (1);
}

/**
 * rd_hstry - reads history from file
 * @data: struct
 *
 * Return: count or 0
 */
int rd_hstry(data_t *data)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = gt_hstry_fle(data);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			bld_hstry_lst(data, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		bld_hstry_lst(data, buf + last, linecount++);
	free(buf);
	data->histcount = linecount;
	while (data->histcount-- >= HIST_MAX)
		dlt_nd_ndx(&(data->history), 0);
	rnmbr_hstry(data);
	return (data->histcount);
}

/**
 * bld_hstry_lst - adds entry to a history linked list
 * @info: Struct containing arguments.
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: 0
 */
int bld_hstry_lst(data_t *data, char *buf, int linecount)
{
	list_t *node = NULL;

	if (data->history)
		node = data->history;
	dd_nd_nd(&node, buf, linecount);

	if (!data->history)
		data->history = node;
	return (0);
}

/**
 * rnmbr_hstry - renumbers the linked list history 
 * @data: Structure containing arguments.
 * Return: the new histcount
 */
int rnmbr_hstry(data_t *data)
{
	list_t *node = data->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (data->histcount = i);
}
