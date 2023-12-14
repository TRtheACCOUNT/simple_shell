#include "shell.h"

/**
 * hsh - main shell loop
 * @data: info struct
 * @av: the argument vector from main()
 *
 * Return: 0 or 1 or error
 */
int hsh(data_t *data, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(data);
		if (reciprocative(data))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(data);
		if (r != -1)
		{
			set_info(data, av);
			builtin_ret = find_builtin(data);
			if (builtin_ret == -1)
				find_cmd(data);
		}
		else if (reciprocative(data))
			_putchar('\n');
		free_info(info, 0);
	}
	wrt_hstry(data);
	fr_nf(data, 1);
	if (!reciprocative(data) && data->status)
		exit(data->status);
	if (builtin_ret == -2)
	{
		if (data->err_num == -1)
			exit(data->status);
		exit(data->err_num);
	}
	return (builtin_ret);
}

/**
 * fnd_bltn - finds a builtin command
 * @data: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 	0 if builtin executed successfully,
 * 	1 if builtin found but not successful,
 * 	2 if builtin signals exit()
 */
int find_builtin(data_t *data)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _theexit},
		{"env", _ownenv},
		{"help", _ownhelp},
		{"history", _ownhistory},
		{"stenv", _ownstenv},
		{"ownunsetenv", _owunsetenv},
		{"cd", _oncd},
		{"alias", _ownalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_ownstrcmp(data->argv[0], builtintbl[i].type) == 0)
		{
			data->line_count++;
			built_in_ret = builtintbl[i].func(data);
			break;
		}
	return (built_in_ret);
}

/**
 * fnd_cmd - finds a command in PATH
 * @data: info struct
 *
 * Return: void
 */
void fnd_cmd(data_t *data)
{
	char *path = NULL;
	int i, k;

	data->path = data->argv[0];
	if (data->linecount_flag == 1)
	{
		data->line_count++;
		data->linecount_flag = 0;
	}
	for (i = 0, k = 0; data->arg[i]; i++)
		if (!delim(data->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = fnd_pth(info, _gtenv(data, "PATH="), data->argv[0]);
	if (path)
	{
		data->path = path;
		frk_cmd(data);
	}
	else
	{
		if ((reciprocative(data) || _getenv(data, "PATH=")
					|| data->argv[0][0] == '/') && s_cmd(data, data->argv[0]))
			fork_cmd(info);
		else if (*(data->arg) != '\n')
		{
			data->status = 127;
			puts_error(data, "not found\n");
		}
	}
}

/**
 * frk_cmd - forks a an exec thread to run cmd
 * @data: the parameter & return info struct
 *
 * Return: void
 */
void frk_cmd(data_t *data)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(data->path, info->argv, get_environ(info)) == -1)
		{
			free_data(data, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(data->status));
		if (WIFEXITED(data->status))
		{
			data->status = WEXITSTATUS(data->status);
			if (data->status == 126)
				puts_error(data, "Permission denied\n");
		}
	}
}
