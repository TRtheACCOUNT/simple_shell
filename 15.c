#include "shell.h"

/**
 * s_cmd – tells if a command is exuctuable
 * @data: data struct
 * @path: path to the file
 *
 * Return: 1 or 0
 */
int s_cmd(data_t *data, char *path)
{
	struct stat st;

	(void)data;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dp_chrs - duplicates characters
 * @pathstr: the PATH string
 * @start: first of index
 * @stop: last of index
 *
 * Return: pointer to new buffer
 */
char *dp_chrs(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * fnd_pth – finds the cmd in the path
 * @data: the data struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *fnd_pth(data_t *data, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_ownstrlen(cmd) > 2) && ownstarts_with(cmd, "./"))
	{
		if (s_cmd(data, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dp_chrs(pathstr, curr_pos, i);
			if (!*path)
				_ownstrcat(path, cmd);
			else
			{
				_ownstrcat(path, "/");
				_ownstrcat(path, cmd);
			}
			if (s_cmd(data, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
