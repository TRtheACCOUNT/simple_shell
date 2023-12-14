#include "shell.h"

/**
 * _thexit - exits the shell
 * @data: Struct containing arguments
 * Return: given exit status
 * or 0 if data.argv[0] != "exit"
 */
int _thexit(data_t *data)
{
	int e;
	if (data->argv[1]) 
	{
		e = _cnvrtnt(data->argv[1]);
		if (e == -1)
		{
			data->status = 2;
			puts_error(data, "Illegal number: ");
			_owneputs(data->argv[1]);
			_owneputchar('\n');
			return (1);
		}
		data->err_num = _cnvrtnt(data->argv[1]);
		return (-2);
	}
	data->err_num = -1;
	return (-2);
}

/**
 * _oncd - changes directory
 * @data: Struct contains arguments
 * Return: 0
 */
int _oncd(data_t *data)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_ownputs("fail");
	if (!data->argv[1])
	{
		dir = _gtenv(data, "Place=");
		if (!dir)
			chdir_ret = chdir((dir = _gtenv(data, "thepwd=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_ownstrcmp(data->argv[1], "-") == 0)
	{
		if (!_gtenv(data, "prpwd="))
		{
			_ownputs(s);
			_ownputchar('\n');
			return (1);
		}
		_ownputs(_gtenv(data, "oldpwd=")), _ownputchar('\n');
		chdir_ret = chdir((dir = _gtenv(data, "oldpwd=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(data->argv[1]);
	if (chdir_ret == -1)
	{
		puts_error(data, "can't ");
		_owneputs(data->argv[1]), _owneputchar('\n');
	}
	else
	{
		_stenv(data, "oldpwd", _gtenv(data, "pwd="));
		_stenv(data, "pwd", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _ownhelp - changes the directory
 * @data: Structure containing arguments.
 * Return: 0
 */
int _ownhelp(data_t *data)
{
	char **arg_array;

	arg_array = data->argv;
	_ownputs("not working yet \n");
	if (0)
		_ownputs(*arg_array); 
	return (0);
}
