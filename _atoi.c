#include "shell.h"

/**
 * interactive - returns true if shell is in interactive mode
 * @info: struct address
 * Return: 1 if in interactive mode,
 * 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
 * is_delim - checks if character is a delimeter
 * @g: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char g, char *delim)
{
	while (*delim)
	{
		if (*delim++ == g)
		{
			return (1);
		}
	}
	return (0);
}
/**
 *_isalpha - checks for alphabetic character
 *@g: The character to input
 *Return: 1 if g is alphabetic, 0 otherwise
 */

int _isalpha(int g)
{
	if ((g >= 'a' && g <= 'z') || (g >= 'A' && g <= 'Z'))
	{
		return (1);
	}
	else
		return (0);
}
/**
 *_atoi - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *str)
{
	int sign = 1, flag = 0, output, x;
	unsigned int result = 0;

	for (x = 0;  str[x] != '\0' && flag != 2; x++)
	{
		if (str[x] == '-')
			sign *= -1;

		if (str[x] >= '0' && str[x] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[x] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
