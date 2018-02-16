/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 01:34:50 by rfabre            #+#    #+#             */
/*   Updated: 2018/01/25 03:38:23 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (buf[2] == 65)
		ft_arrow_up(line);
	else if (buf[2] == 66)
		ft_arrow_down(line);
	else if (buf[2] == 68)
		ft_left_arrow(buf, line);
	else
		ft_right_arrow(buf, line);
	if (line->select_mode)
	{
		line->end_select = line->cursor_pos - 2;
		ft_go_start(line, buf);
		ft_highlight(line, buf);
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
