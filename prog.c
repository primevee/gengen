#include "shell.h"

/**
 * main - Programs entry point
 * @ac: Number of parameters passed
 * @av: Name of the program
 * Return: 0
 */

int main(__attribute__((unused)) int ac, char **av)
{
	char *line;
	size_t size;
	int command_counter;

	command_counter = 0;
	signal(SIGINT, SIG_IGN);
	do {
		command_counter++;
		line = NULL;
		size = 0;
		parse_line(line, size, command_counter, av);

	} while (1);

	return (0);
}

/**
 * parse_line - function that splits the command line
 * @line: A pointer to a string
 * @size: the size of the command
 * @command_counter: number of commands in the line
 * @av: Name of the program that runs the shell
 */
void parse_line(char *line, size_t size, int command_counter, char **av)
{
	int i;
	ssize_t read_len;
	int token_count;
	char **param_array;
	const char *delim = "\n\t ";

	token_count = 0;
	if (isatty(STDIN_FILENO) == 1)
	write(STDOUT_FILENO, ">$ ", 3);
	read_len = getline(&line, &size, stdin);
	if (read_len != -1)
	{
		param_array = getRoot(line, delim, token_count);
		if (param_array[0] == NULL)
		{
			_free(2, param_array, line);
			return;
		}
		i = builtin(param_array, line);
		if (i == -1)
			_child(param_array, line, command_counter, av);
		for (i = 0; param_array[i] != NULL; i++)
			free(param_array[i]);
		_free(2, param_array, line);
	}
	else
		exit_cmd(line);
}

/**
 * pFinder - find the full path
 * @command: Represents a command
 * Return: string with the full program path
 */
char *pFinder(char *command)
{
	char *str = "PATH";
	char *constructed;
	char **path_tokens;
	int index;
	char *directory;

	index = _findPath(str);
	path_tokens = split_path(index, str);
	if (path_tokens == NULL)
		return (NULL);

	directory = _dirs(path_tokens, command);
	if (directory == NULL)
	{
		_free2(path_tokens);
		return (NULL);
	}

	constructed = build_path(directory, command);
	if (constructed == NULL)
	{
		_free2(path_tokens);
		return (NULL);
	}

	_free2(path_tokens);

	return (constructed);
}

/**
 * _findPath - Finds index of env variable
 * @str: Env variable
 * Return: Upon success, returns the index of the env variable,
 * otherwise returns -1.
 */
int _findPath(char *str)
{
	int i;
	int len;
	int j;

	len = _strlen(str);
	for (i = 0; environ[i] != NULL; i++)
	{
		for (j = 0; j < len; j++)
		{
			if (environ[i][j] != str[j])
				break;
		}
		if (j == len && environ[i][j] == '=')
			return (i);
	}
	return (-1);
}

/**
 * split_path - Separate a string in an array of directories
 * @index: Index of the path in the env variables
 * @str: string to tokenize
 * Return: array of pointer to strings
 */
char **split_path(int index, char *str)
{
char *env_var;
	int token_count;
	const char *delim = ":\n";
	char **path_tokens;
	int len;

	len = _strlen(str);
	token_count = 0;
	env_var = environ[index] + (len + 1);
	path_tokens = getRoot(env_var, delim, token_count);
	if (path_tokens == NULL)
		return (NULL);
	return (path_tokens);
}
