#include "shell.h"
/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t g = 0;
	size_t len_pm = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		g = getline(buf, &len_pm, stdin);
#else
		g = _getline(info, buf, &len_pm);
#endif
		if (g > 0)
		{
			if ((*buf)[g - 1] == '\n')
			{
				(*buf)[g - 1] = '\0';
				g--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = g;
				info->cmd_buf = buf;
			}
		}
	}
	return (g);
}
/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t x, y, len;
	ssize_t g = 0;
	char **buf_p = &(info->arg), *ptr;

	_putchar(BUF_FLUSH);
	g = input_buf(info, &buf, &len);
	if (g == -1)
		return (-1);
	if (len)
	{
		y = x;
		ptr = buf + x;

		check_chain(info, buf, &y, x, len);
		while (y < len)
		{
			if (is_chain(info, buf, &y))
				break;
			y++;
		}

		x = y + 1;
		if (x >= len)
		{
			x = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = ptr;
		return (_strlen(ptr));
	}

	*buf_p = buf;
	return (g);
}
/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 * Return: g
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t g = 0;

	if (*i)
		return (0);
	g = read(info->readfd, buf, READ_BUF_SIZE);
	if (g >= 0)
		*i = g;
	return (g);
}
/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t x, len;
	size_t j;
	ssize_t g = 0, s = 0;
	char *p = NULL, *new_p = NULL, *ch;

	p = *ptr;
	if (p && length)
		s = *length;
	if (x == len)
		x = len = 0;

	g = read_buf(info, buf, &len);
	if (g == -1 || (g == 0 && len == 0))
		return (-1);

	ch = _strchr(buf + x, '\n');
	j = ch ? 1 + (unsigned int)(ch - buf) : len;
	new_p = _realloc(p, s, s ? s + j : j + 1);
	if (!new_p)
	{
		return (p ? free(p), -1 : -1);
	}
	if (s)
		_strncat(new_p, buf + x, j - x);
	else
		_strncpy(new_p, buf + x, j - x + 1);

	s += j - x;
	x = j;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
