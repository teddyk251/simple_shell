#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **_copyenv(void)
{
	char **new_environment;
	size_t size;
	int index;

	for (size = 0; environ[size]; size++)
		;

	new_environment = malloc(sizeof(char *) * (size + 1));
	if (!new_environment)
		return (NULL);

	for (index = 0; environ[index]; index++)
	{
		new_environment[index] = malloc(_strlen(environ[index]) + 1);

		if (!new_environment[index])
		{
			for (index--; index >= 0; index--)
				free(new_environment[index]);
			free(new_environment);
			return (NULL);
		}
		_strcpy(new_environment[index], environ[index]);
	}
	new_environment[index] = NULL;

	return (new_environment);
}

/**
 * free_env - Frees the the environment copy.
 */
void free_env(void)
{
	int index;

	for (index = 0; environ[index]; index++)
		free(environ[index]);
	free(environ);
}

/**
 * _getenv - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_getenv(const char *var)
{
	int index, len;

	len = _strlen(var);
	for (index = 0; environ[index]; index++)
	{
		if (_strncmp(var, environ[index], len) == 0)
			return (&environ[index]);
	}

	return (NULL);
}
