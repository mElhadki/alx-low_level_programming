#include "holberton.h"
#include <stdlib.h>

/**
 * argstostr - Concatenates all the arguments of the program
 * @ac: The number of arguments
 * @av: An array of pointers to the arguments
 *
 * Return: A pointer to the new string, or NULL on failure
 */
char *argstostr(int ac, char **av)
{
    int i, j, k = 0, total_len = 0;
    char *str;

    if (ac == 0 || av == NULL)
        return (NULL);

    for (i = 0; i < ac; i++)
    {
        for (j = 0; av[i][j]; j++)
            total_len++;
    }

    str = malloc(total_len + ac + 1); // +1 for the newline character after each argument
    if (str == NULL)
        return (NULL);

    for (i = 0; i < ac; i++)
    {
        for (j = 0; av[i][j]; j++)
            str[k++] = av[i][j];
        str[k++] = '\n'; // Add a newline character after each argument
    }
    str[k] = '\0'; // Add the null-terminator at the end

    return (str);
}
