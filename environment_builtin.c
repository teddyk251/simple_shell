#include "shell.h"

int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shellby_env - Prints the current environment.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */
int shellby_env(char **args, char __attribute__((__unused__)) **front)
{
	int index;
	char nc = '\n';

	if (!environment)
		return (-1);

	for (index = 0; environment[index]; index++)
	{
		write(STDOUT_FILENO, environment[index], _strlen(environment[index]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)args;
	return (0);
}

/**
 * shellby_setenv - Changes or adds an environmental variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the name of the new or existing PATH variable.
 *              args[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environment, *new_value;
	size_t size;
	int index;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_value = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_value)
		return (create_error(args, -1));
	_strcpy(new_value, args[0]);
	_strcat(new_value, "=");
	_strcat(new_value, args[1]);

	env_var = _getenv(args[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environment[size]; size++)
		;

	new_environment = malloc(sizeof(char *) * (size + 2));
	if (!new_environment)
	{
		free(new_value);
		return (create_error(args, -1));
	}

	for (index = 0; environment[index]; index++)
		new_environment[index] = environment[index];

	free(environment);
	environment = new_environment;
	environment[index] = new_value;
	environment[index + 1] = NULL;

	return (0);
}

/**
 * shellby_unsetenv - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environment;
	size_t size;
	int index, index2;

	if (!args[0])
		return (create_error(args, -1));
	env_var = _getenv(args[0]);
	if (!env_var)
		return (0);

	for (size = 0; environment[size]; size++)
		;

	new_environment = malloc(sizeof(char *) * size);
	if (!new_environment)
		return (create_error(args, -1));

	for (index = 0, index2 = 0; environment[index]; index++)
	{
		if (*env_var == environment[index])
		{
			free(*env_var);
			continue;
		}
		new_environment[index2] = environment[index];
		index2++;
	}
	free(environment);
	environment = new_environment;
	environment[size - 1] = NULL;

	return (0);
}
