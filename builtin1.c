#include "shell.h"
/**
 * _myhistory - displays the history list, one
 * command by line, precededwith line numbers,
 * starting at 0.
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}
/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @s: the string alias
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *s)
{
	char *ptr, g;
	int r;

	ptr = _strchr(s, '=');
	if (!ptr)
		return (1);
	g = *ptr;
	*ptr = 0;
	r = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, s, -1)));
	*ptr = g;
	return (r);
}
/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @s: the string alias
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *s)
{
	char *ptr;

	ptr = _strchr(s, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (unset_alias(info, s));

	unset_alias(info, s);
	return (add_node_end(&(info->alias), s, 0) == NULL);
}
/**
 * print_alias - prints an alias string
 * @node: the alias node
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *ptr = NULL, *c = NULL;

	if (node)
	{
		ptr = _strchr(node->s, '=');
		for (c = node->str; c <= ptr; c++)
			_putchar(*c);
		_putchar('\'');
		_puts(ptr + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int x = 0;
	char *ptr = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (x = 1; info->argv[x]; x++)
	{
		ptr = _strchr(info->argv[x], '=');
		if (ptr)
			set_alias(info, info->argv[x]);
		else
			print_alias(node_starts_with(info->alias, info->argv[x], '='));
	}

	return (0);
}
