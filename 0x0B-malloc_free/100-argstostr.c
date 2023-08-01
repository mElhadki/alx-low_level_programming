#include "holberton.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * argstostr - Concatenates all the arguments of the program.
 * @ac: The argument count.
 * @av: The argument vector (array of strings).
 *
 * Return: A pointer to a new string containing the concatenated arguments,
 *         separated by a newline character. Returns NULL on failure.
 */
char *argstostr(int ac, char **av)
{
    if (ac == 0 || av == NULL)
        return NULL;

    int total_length = 0;
    int i, j;
    char *concatenated_str;

    // Calculate the total length required for the concatenated string
    for (i = 0; i < ac; i++)
    {
        for (j = 0; av[i][j]; j++)
            total_length++;
    }

    // Add space for newlines between arguments (ac - 1)
    total_length += ac - 1;

    // Allocate memory for the concatenated string
    concatenated_str = malloc(total_length + 1);

    if (concatenated_str == NULL)
        return NULL;

    // Copy the arguments and add newlines
    int index = 0;
    for (i = 0; i < ac; i++)
    {
        for (j = 0; av[i][j]; j++)
            concatenated_str[index++] = av[i][j];

        // Add newline except for the last argument
        if (i < ac - 1)
            concatenated_str[index++] = '\n';
    }

    // Null-terminate the concatenated string
    concatenated_str[index] = '\0';

    return concatenated_str;
}
