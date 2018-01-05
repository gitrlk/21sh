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

	ioctl(STDERR_FILENO, TIOCGWINSZ, &sz);
	tcgetattr(0, &attributes);
	attributes.c_lflag &= ~(ICANON);
	attributes.c_lflag &= ~(ECHO);
	attributes.c_cc[VMIN] = 1;
	attributes.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &attributes);
	return (sz);
}

static void handle_key(int buf, t_edit *line)
{
	if (ft_isascii(buf))
	{
		line->cursor_pos++;
		line->max_size++;
	}
	if ((buf == 4476699) && (line->cursor_pos > 0))
	{
			line->cursor_pos--;
			ft_putstr("\033[1D");
	}
	else if ((buf == 4411163) && (line->cursor_pos < line->max_size))
	{
			line->cursor_pos++;
			ft_putstr("\033[1C");
	}
}

void			ft_line_reset(t_edit *line)
{
	line->cursor_pos = 0;
	line->line_number = 0;
	line->max_size = 0;
}

int				main(int ac, char **av, char **envp)
{
	int buf;
	(void)ac;
	(void)av;
	(void)envp;
	t_edit *line;
	int ret;

	ret = 0;
	buf = 0;
	line = ft_memalloc(sizeof(t_edit));
	ft_line_reset(line);
	line->sz = ft_init();
	while (42)
	{
		ft_prompt();
		while ((ret = read(0, &buf, 8)) && (buf != 10))
		{
			if (ft_isascii(buf))
				ft_putchar(buf);
			handle_key(buf, line);
			buf = 0;
		}
		ft_line_reset(line);
		ft_putchar('\n');
	}
	return 0;
}
