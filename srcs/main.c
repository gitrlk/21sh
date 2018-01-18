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
	size_t i;

	i = 0;
	if (line->cursor_pos)
	{
		tmp = ft_strndup(line->line, line->cursor_pos - 3);
		tmp2 = ft_strsub(line->line, line->cursor_pos - 3 , line->max_size);
		ft_putchar(buf[0]);
		tmp3 = ft_freejoinstr(tmp, buf);
		free (line->line);
		line->line = ft_freejoinstr(tmp3, tmp2);
		free (tmp2);
		tputs(tgetstr("cd", NULL), 1, ft_pointchar);
		ft_putstr(tmp2);
		while (i < ft_strlen(tmp2))
		{
			tputs(tgetstr("le", NULL), 1, ft_pointchar);
			i++;
		}
	}
	else
	{
		tmp = NULL;
		tmp2 = NULL;
		tmp3 = NULL;
	}
}

void ft_delete(t_edit *line)
{
	char *tmp;
	char *tmp2;

	if ((line->cursor_pos == line->max_size) && (line->cursor_pos > 2))
	{
		tmp = ft_strndup(line->line, ft_strlen(line->line) - 1);
		free (line->line);
		line->line = tmp;
		line->cursor_pos--;
		line->max_size--;
	}
	else if ((line->cursor_pos != line->max_size) && (line->cursor_pos > 2))
	{
  	tmp = ft_strndup(line->line, (line->cursor_pos - 3));
		tmp2 = ft_strsub(line->line, (line->cursor_pos - 2), (ft_strlen(line->line) - line->cursor_pos) + 3);
		free (line->line);
		ft_putchar('\n');
		ft_putstr("tmp1->");
		ft_putstr(tmp);
		ft_putchar('\n');
		ft_putstr("tmp2->");
		ft_putstr(tmp2);
		line->line = ft_strjoin(tmp, tmp2);
		free (tmp);
		free (tmp2);
		line->cursor_pos--;
		line->max_size--;
	}
}


void handle_key(char *buf, t_edit *line)
{
	if (ft_isprint(buf[0]))
	{
		line->cursor_pos++;
		line->max_size++;
	}
	if (buf[0] == 27)
		ft_isarrow(buf, line);
	else if ((line->cursor_pos == line->max_size) && (ft_isprint(buf[0])))
	{
		line->line = ft_freejoinstr(line->line, buf);
		ft_putchar(buf[0]);
	}
	else if ((line->cursor_pos != line->max_size) && (ft_isprint(buf[0])))
		ft_insert(buf, line);
	else if (buf[0] == 127)
		ft_delete(line);
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
		}
		ft_putchar('\n');
		ft_putstr(line->line);
		if (ft_strequ(line->line, "clear"))
			tputs(tgetstr("cl", NULL), 1, ft_pointchar);
		if (ft_strequ(line->line, "exit"))
			exit(0);
		ft_line_reset(line);
	}
	return 0;
}
