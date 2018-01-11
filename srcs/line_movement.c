#include "../includes/sh.h"

void ft_left_arrow(char *buf, t_edit *line)
{
	if (buf[2] == 68)
	{
		if (line->cursor_pos > 0)
		{
			line->cursor_pos--;
			ft_putstr("\033[1D");
		}
		if (((line->line_number > 0) && (line->cursor_pos + 2 == line->sz.ws_col))
		|| ((line->line_number > 0) && (line->cursor_pos == line->sz.ws_col - 1)))
			line->line_number--;
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
		// if (line->line_number == 0)
		// {
			if ((line->cursor_pos) == line->sz.ws_col - 1)
			{
				tputs(tgetstr("do", NULL), 1, ft_pointchar);
				tputs(tgetstr("cr", NULL), 1, ft_pointchar);
			}
		// }
		// else if (line->line_number > 0)
		// {
		// 	ft_putstr("OLAOLA");
		// 	if ((line->cursor_pos) == line->sz.ws_col)
		// 	{
		// 		tputs(tgetstr("do", NULL), 1, ft_pointchar);
		// 		tputs(tgetstr("cr", NULL), 1, ft_pointchar);
		// 	}
		// }
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
