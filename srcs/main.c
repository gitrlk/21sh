#include "../includes/sh.h"

int				ft_pointchar(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (0);
}

void			ft_prompt(void)
{
	ft_putstr(TURQUOISE);
	ft_putstr("$>");
	ft_putstr(DEFAULT);
}

struct winsize		ft_init(void)
{
	struct winsize sz;
	struct termios attributes;
	char			*name_term;

	if ((name_term = getenv("TERM")) == NULL)
		ft_putendl("<TERM> VARIABLE NOT FOUND");
	if (tgetent(NULL, name_term) == ERR)
		ft_putendl("VARIABLE NOT VALID");
	ioctl(STDERR_FILENO, TIOCGWINSZ, &sz);
	tcgetattr(0, &attributes);
	attributes.c_lflag &= ~(ICANON);
	attributes.c_lflag &= ~(ECHO);
	attributes.c_cc[VMIN] = 1;
	attributes.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &attributes);
	return (sz);
}

void ft_insert(char *buf, t_edit *line)
{
	char *tmp;
	char *tmp2;
	char *tmp3;
	int i;

	i = 0;
	tmp = ft_strndup(line->line, line->cursor_pos - 3);
	tmp2 = ft_strsub(line->line, line->cursor_pos - 3 , line->max_size);
	ft_putchar(buf[0]);
	tmp3 = ft_freejoinstr(tmp, buf);
	free (line->line);
	line->line = ft_freejoinstr(tmp3, tmp2);
	tmp2 = ft_strsub(line->line, line->cursor_pos - 2 , line->max_size);
	while (i < line->max_size)
	{
		buf[2] = 68;
		ft_left_arrow(buf, line);
		i++;
	}
	i = 0;
	tputs(tgetstr("cd", NULL), 1, ft_pointchar);
	ft_putstr(line->line);
	line->cursor_pos = ft_strlen(line->line) + 2;
	while ((size_t)i < ft_strlen(tmp2))
	{
		buf[2] = 68;
		ft_left_arrow(buf, line);
		i++;
	}
}

void ft_delete(char *buf, t_edit *line)
{
	char *tmp;
	char *tmp2;
	int i;

	i = 0;
	if ((line->cursor_pos == line->max_size) && (line->cursor_pos > 2))
	{
		i = 0;
		tmp = ft_strndup(line->line, ft_strlen(line->line) - 1);
		free (line->line);
		line->line = tmp;
		while (i < line->max_size)
		{
			buf[2] = 68;
			ft_left_arrow(buf, line);
			i++;
		}
		line->cursor_pos--;
		line->max_size--;
		tputs(tgetstr("cd", NULL), 1, ft_pointchar);
		ft_putstr(line->line);
		line->cursor_pos = ft_strlen(line->line) + 2;
	}
	else if ((line->cursor_pos != line->max_size) && (line->cursor_pos > 2))
	{
  		tmp = ft_strndup(line->line, (line->cursor_pos - 3));
		tmp2 = ft_strsub(line->line, (line->cursor_pos - 2),
				(ft_strlen(line->line) - line->cursor_pos) + 3);
		free (line->line);
		line->line = ft_strjoin(tmp, tmp2);
		free (tmp);
		free (tmp2);
		while (i < line->max_size)
		{
			buf[2] = 68;
			ft_left_arrow(buf, line);
			i++;
		}
		line->cursor_pos--;
		line->max_size--;
		i = 0;
		tputs(tgetstr("cd", NULL), 1, ft_pointchar);
		ft_putstr(line->line);
		line->cursor_pos = ft_strlen(line->line) + 2;
		while ((size_t)i < ft_strlen(tmp2))
		{
			buf[2] = 68;
			ft_left_arrow(buf, line);
			i++;
		}
	}
}

void ft_wordleft(char *buf, t_edit *line)
{
	int i;

	i = line->cursor_pos - 3;
	if (ft_isascii(line->line[i]))
	{
		if (line->line[i] == ' ')
			while(line->line[i] == ' ')
			{
				buf[0] = 27;
				buf[1] = 91;
				buf[2] = 68;
				i--;
				ft_left_arrow(buf, line);
			}
		while (line->line[i] != ' ')
		{
			buf[0] = 27;
			buf[1] = 91;
			buf[2] = 68;
			i--;
			ft_left_arrow(buf, line);
		}
	}
}

void ft_wordright(char *buf, t_edit *line)
{
	int i;

	i = line->cursor_pos - 3;
	if (ft_isascii(line->line[i]))
	{
		if (line->line[i] == ' ')
			while(line->line[i] == ' ')
			{
				buf[0] = 27;
				buf[1] = 91;
				buf[2] = 67;
				i++;
				ft_right_arrow(buf, line);
			}
		while (line->line[i] != ' ')
		{
			buf[0] = 27;
			buf[1] = 91;
			buf[2] = 67;
			i++;
			ft_right_arrow(buf, line);
		}
	}
}

void ft_endkey(char *buf, t_edit *line)
{
	while (line->cursor_pos < line->max_size)
	{
		buf[0] = 27;
		buf[1] = 91;
		buf[2] = 67;
		ft_right_arrow(buf, line);
	}
}

void ft_homekey(char *buf, t_edit *line)
{
	while (line->cursor_pos > 2)
	{
		buf[0] = 27;
		buf[1] = 91;
		buf[2] = 68;
		ft_left_arrow(buf, line);
	}
}

void handle_key(char *buf, t_edit *line)
{
	if (ft_isprint(buf[0]))
	{
		line->cursor_pos++;
		line->max_size++;
	}
	if ((line->cursor_pos == line->max_size) && (ft_isprint(buf[0])))
	{
		line->line = ft_freejoinstr(line->line, buf);
		ft_putchar(buf[0]);
	}
	if (buf[0] == 27 && buf[1] == 91 && ((buf[2] == 67) || (buf[2] == 68)))
		ft_isarrow(buf, line);
	else if ((line->cursor_pos != line->max_size) && (ft_isprint(buf[0])))
		ft_insert(buf, line);
	else if (buf[0] == 127)
		ft_delete(buf, line);
	else if (buf[0] == 5 && buf[1] == 0 && buf[2] == 0)
		ft_wordleft(buf, line);
	else if (buf[0] == 18 && buf[1] == 0 && buf[2] == 0)
		ft_wordright(buf, line);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 72)
		ft_homekey(buf, line);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 70)
		ft_endkey(buf, line);
}

void			ft_line_reset(t_edit *line)
{
	free (line->line);
	line->cursor_pos = 2;
	line->max_size = 2;
	line->line = ft_memalloc(sizeof(char));
}

int				main(int ac, char **av, char **envp)
{
	char buf[3];
	(void)ac;
	(void)av;
	(void)envp;
	t_edit *line;
	int ret;

	ret = 0;
	line = ft_memalloc(sizeof(t_edit));
	ft_line_reset(line);
	line->sz = ft_init();
	while (42)
	{
		ft_prompt();
		while ((ret = read(0, &buf, 3)) && ft_strcmp(buf, "\n"))
		{
			// ft_putnbr(buf[0]);
			// ft_putchar('\n');
			// ft_putnbr(buf[1]);
			// ft_putchar('\n');
			// ft_putnbr(buf[2]);
			// ft_putchar('\n');
			buf[ret] = '\0';
			handle_key(buf, line);
			ft_bzero(buf, sizeof(buf));
		}
		// ft_putchar('\n');
		// ft_putstr(line->line);
		if (ft_strequ(line->line, "clear"))
			tputs(tgetstr("cl", NULL), 1, ft_pointchar);
		if (ft_strequ(line->line, "exit"))
			exit(0);
		// ft_putchar('\n');
		// ft_putstr("NBR / max_size / cursor_pos / line");
		// ft_putchar('\n');
		// ft_putnbr(line->max_size);
		ft_putchar('\n');
		ft_putnbr(line->cursor_pos);
		ft_putchar('\n');
		// ft_putnbr(ft_strlen(line->line) + 2);
		// ft_putchar('\n');
		ft_line_reset(line);
	}
	return 0;
}
