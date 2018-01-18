#include "../includes/sh.h"

void ft_left_arrow(char *buf, t_edit *line)
{
	if (buf[2] == 68)
	{
		if (line->cursor_pos >= 3)
		{
			line->cursor_pos--;
			ft_putstr("\033[1D");
		}
	}
}

void ft_right_arrow(char *buf, t_edit *line)
{
	if (buf[2] == 67)
	{
		if (line->cursor_pos < line->max_size)
		{
			line->cursor_pos++;
			ft_putstr("\033[1C");
		}
		if (((line->cursor_pos) % line->sz.ws_col) == 0)
		{
			tputs(tgetstr("do", NULL), 1, ft_pointchar);
			tputs(tgetstr("cr", NULL), 1, ft_pointchar);
		}
	}
}

void ft_isarrow(char *buf, t_edit *line)
{
	if ((buf[1] == 91) && (line->cursor_pos >= 0))
	{
		ft_left_arrow(buf, line);
		ft_right_arrow(buf, line);
	}
}
