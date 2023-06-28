#include "shell.h"
/**
 * _strlen - Calculates the lenght of a string.
 * @str: String that needs length to be found.
 * Return: the length of a string. otherwise 0.
 */
int _strlen(char *str)
{
	int i;

	if (str == NULL)
		return (0);
	for (i = 0; str[i] != '\0'; i++)
		;
	return (i);
}

/**
 * _free2 - Free double pointer variables.
 * @to_be_freed: The address of the elements that need to be freed.
 */
void _free2(char **to_be_freed)
{
	int index;

	for (index = 0; to_be_freed[index] != NULL; index++)
		free(to_be_freed[index]);
	free(to_be_freed);
}

/**
 * _free - free a pointers to a string.
 * @n: The number of pointers to free.
 */
void _free(int n, ...)
{
	int i;
	char *str;
	va_list a_list;

	va_start(a_list, n);
	for (i = 0; i < n; i++)
	{
		str = va_arg(a_list, char*);
		if (str == NULL)
			str = "(nil)";
		free(str);
	}
	va_end(a_list);
}


/**
 * printErr - Prints a message of error when a comand is not found.
 * @count: number of commands run on the shell.
 * @av: The name of the program running the shell.
 * @command: specific command.
 */
void printErr(char *av, int count, char *command)
{
	print_str(av, 1);
	print_str(": ", 1);
	print_number(count);
	print_str(": ", 1);
	print_str(command, 1);
}

/**
 * execErr - Prints exec errors.
 * @av: The name of the program running the shell.
 * @count: how many commands have been entered.
 * @tmp_command: The command that filed.
 */

void execErr(char *av, int count, char *tmp_command)
{
	printErr(av, count, tmp_command);
	print_str(": ", 1);
	perror("");
	exit(1);
}
