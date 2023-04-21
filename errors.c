#include "shell.h"
/**
 *_eputs - prints an input string
 * @s: the string to be printed
 * Return: Nothing
 */
void _eputs(char *s)
{
	int x = 0;

	if (!s)
	{
		return;
	}
	while (s[x] != '\0')
	{
		_eputchar(s[x]);
		x++;
	}
}
/**
 * _eputchar - writes the character c to stderr
 * @g: The character to print
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char g)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (g == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (g != BUF_FLUSH)
		buf[x++] = g;
	return (1);
}
/**
 * _putfd - writes the character c to given fd
 * @g: The character to print
 * @fd: The filedescriptor to write to
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char g, int fd)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (g == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(fd, buf, x);
		x = 0;
	}
	if (g != BUF_FLUSH)
	{
		buf[x++] = g;
	}
	return (1);
}
/**
 *_putsfd - prints an input string
 * @s: the string to be printed
 * @fd: the filedescriptor to write to
 * Return: the number of chars put
 */
int _putsfd(char *s, int fd)
{
	int x = 0;

	if (!s)
		return (0);
	while (*s)
	{
		x += _putfd(*s++, fd);
	}
	return (x);
}
