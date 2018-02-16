/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 01:34:48 by rfabre            #+#    #+#             */
/*   Updated: 2018/01/25 20:53:14 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

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

	i = line->cursor_pos - 2;
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

void ft_delete(char *buf, t_edit *line)
{
	char *tmp;
	char *tmp2;
	int i;

	i = 0;
	if ((line->cursor_pos == line->max_size) && (line->cursor_pos > 2))
	{
		tmp = ft_strndup(line->line, ft_strlen(line->line) - 1);
		free (line->line);
		line->line = tmp;
		ft_move_it(line, buf, 0);
	}
	else if ((line->cursor_pos != line->max_size) && (line->cursor_pos > 2))
	{
		tmp = ft_strndup(line->line, (line->cursor_pos - 3));
		tmp2 = ft_strsub(line->line, (line->cursor_pos - 2),
				(ft_strlen(line->line) - line->cursor_pos) + 3);
		free (line->line);
		line->line = ft_freejoinstr(tmp, tmp2);
		ft_move_it(line, buf, 0);
		while ((size_t)i < ft_strlen(tmp2))
		{
			buf[2] = 68;
			ft_left_arrow(buf, line);
			i++;
		}
	}
}

void ft_move_it(t_edit *line, char *buf, int check)
{
	int i;

	i = 0;
	while (i < line->max_size)
	{
		buf[2] = 68;
		ft_left_arrow(buf, line);
		i++;
	}
	if (check == 1)
		i = 0;
	if (check == 0)
	{
		line->cursor_pos--;
		line->max_size--;
	}
	tputs(tgetstr("cd", NULL), 1, ft_pointchar);
	ft_putstr(line->line);
	line->cursor_pos = ft_strlen(line->line) + 2;
}


void handle_key(char *buf, t_edit *line)
{
	if (!line->select_mode)
	{
		if (ft_isprint(buf[0]))
			add_to_line(line, buf);
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
	if (buf[0] == 27 && buf[1] == 91 && ((buf[2] == 67) || (buf[2] == 68 || buf[2] == 65 || buf[2] == 66))) //65 up 66 down
		ft_isarrow(buf, line);
	else if ((buf[0] == 11) || (buf[0] == 21 ) || (buf[0] == 9) || buf[0] == 16)
		select_copy_cut(line, buf);
}
