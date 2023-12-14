#include "shell.h"

/**
 * npt_buf – gets input
 * @data: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t npt_buf(data_t *data, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
		r = _owngetline(data, buf, &len_p);
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; 
				r--;
			}
			data->linecount_flag = 1;
			rmv_cmnts(*buf);
			bld_hstry_lst(data, *buf, data->histcount++);
			{
				*len = r;
				data->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - removes the newline
 * @data: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(data_t *data)
{
	static char *buf; 
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(data->arg), *p;

	_ownputchar(BUF_FLUSH);
	r = npt_buf(data, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i; 

		check_chain(data, buf, &j, i, len);
		while (j < len) 
		{
			if (chain(data, buf, &j))
				break;
			j++;
		}

		i = j + 1; 
		if (i >= len)
		{
			i = len = 0; 
			data->cmd_buf_type = 0;
		}

		*buf_p = p; 
		return (_ownstrlen(p)); 
	}

	*buf_p = buf; 
	return (r);
}

/**
 * read_buf - reads a buffer
 * @data: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buf(data_t *data, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(data->rdfd, buf, 1024);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _owngetline - gets line from STDIN
 * @data: struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _owngetline(data_t *data, char **ptr, size_t *length)
{
	static char buf[1024];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(data, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _ownstrchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _rllc(p, s, s ? s + k : k + 1);
	if (!new_p) 
		return (p ? free(p), -1 : -1);

	if (s)
		_ownstrncat(new_p, buf + i, k - i);
	else
		_ownstrncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_ownputs("\n");
	_ownputs("$ ");
	_ownputchar(-1);
}
