#include "shell.h"

/**
 * _child - Creates a child process
 * @arg: An array of pointers to strings;  NULL terminated
 * @input: The contents of the read line
 * @count: Inputted command counter
 * @av: program running the shell
 */
void _child(char **arg, char *input, int count, char **av)
{
	int i, isFound, status;
	char *tmp_command, *command;
	struct stat buf;
	pid_t id;

	id = fork();
	if (id == 0)
	{
		tmp_command = arg[0];
		command = pFinder(arg[0]);
		if (command == NULL)
		{
			/*Looking for file in current directory*/
			isFound = stat(tmp_command, &buf);
			if (isFound == -1)
			{
				printErr(av[0], count, tmp_command);
				print_str(": not found", 0);
				_free(2, input, tmp_command);
				for (i = 1; arg[i]; i++)
					free(arg[i]);
				free(arg);
				exit(100);
			}
			/*file exist in cwd or has full path*/
			command = tmp_command;
		}
		arg[0] = command;
		if (arg[0] != NULL)
		{
			if (execve(arg[0], arg, environ) == -1)
				execErr(av[0], count, tmp_command);
		}
	}
	else
		wait(&status);
}

/**
 * getRoot - Interacts with other token functions, and make
 * @input: user input
 * @delim: delimeter to tokenize line
 * @parts_count: holds number of tokens in a string
 * Return: upon success, array of tokens. Otherwise NULL
 */
char **getRoot(char *input, const char *delim, int parts_count)
{
	char **arg;

	parts_count = pCount(input, delim);
	if (parts_count == -1)
	{
		free(input);
		return (NULL);
	}
	arg = split(parts_count, input, delim);
	if (arg == NULL)
	{
		free(input);
		return (NULL);
	}

	return (arg);
}

/**
 * split - Separates a string into array of tokens
 * @parts_count: amount of tokens in the array
 * @input: String separated by a delimeter
 * @delim: delimeter to separate tokens
 * Return: Upon success, a NULL terminated array of pointer to strings.
 * Otherwise returns NULL
 */
char **split(int parts_count, char *input, const char *delim)
{
	int i;
	char **buffer;
	char *part, *input_cp;

	input_cp = _strdup(input);
	buffer = malloc(sizeof(char *) * (parts_count + 1));
	if (buffer == NULL)
		return (NULL);
	part = strtok(input_cp, delim);
	for (i = 0; part != NULL; i++)
	{
		buffer[i] = _strdup(part);
		part = strtok(NULL, delim);
	}
	buffer[i] = NULL;
	free(input_cp);
	return (buffer);
}

/**
 * pCount - Counts tokens in the passed string.
 * @input: String that is separated by an specified delimeter
 * @delim: The desired delimeter to separate tokens.
 * Return: Upon success the total count of the tokens. Otherwise -1.
 */
int pCount(char *input, const char *delim)
{
	char *str;
	char *part;
	int i;

	str = _strdup(input);
	if (str == NULL)
		return (-1);
	part = strtok(str, delim);
	for (i = 0; part != NULL; i++)
		part = strtok(NULL, delim);
	free(str);
	return (i);
}
