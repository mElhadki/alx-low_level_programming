#include <unistd.h>
/**
 * main - Prints a sentence followed by a new line,
 * and includes a quote within the sentence.
 * Return: 1 to indicate failure.
 */
int main(void)
{
    write(2, "and that piece of art is useful\" - Dora Korpar, 2015-10-19\n", 59);
    return 1;
}
