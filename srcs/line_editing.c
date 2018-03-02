/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_editing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:58 by jecarol           #+#    #+#             */
/*   Updated: 2018/03/02 21:53:10 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void ft_wordleft(t_edit *line)
{
	int i;

	i = line->cursor_pos - 2;
	if (i > 0)
	{
		if (ft_isascii(line->line[i]))
		{
			if (line->line[i] == ' ')
				while(line->line[i] == ' ')
				{
					i--;
					ft_left_arrow(line);
				}
			while (line->line[i] != ' ' && i > 0)
			{
				i--;
				ft_left_arrow(line);
			}
		}
	}
}

void ft_wordright(t_edit *line)
{
	int i;

	i = line->cursor_pos - 2;
	if (ft_isascii(line->line[i]))
	{
		if (line->line[i] == ' ')
			while(line->line[i] == ' ')
			{
				i++;
				ft_right_arrow(line);
			}
		while (line->line[i] != ' ' && line->line[i])
		{
			i++;
			ft_right_arrow(line);
		}
	}
}

void ft_delete(t_edit *line)
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
		ft_move_it(line, 0);
	}
	else if ((line->cursor_pos != line->max_size) && (line->cursor_pos > 2))
	{
		tmp = ft_strndup(line->line, (line->cursor_pos - 3));
		tmp2 = ft_strsub(line->line, (line->cursor_pos - 2),
				(ft_strlen(line->line) - line->cursor_pos) + 3);
		free (line->line);
		line->line = ft_freejoinstr(tmp, tmp2);
		ft_move_it(line, 0);
		while ((size_t)i < ft_strlen(tmp2))
		{
			ft_left_arrow(line);
			i++;
		}
	}
}

void ft_move_it(t_edit *line, int check)
{
	int i;

	i = 0;
	while (i < line->max_size)
	{
		ft_left_arrow(line);
		i++;
	}
	if (check == 0)
	{
		line->cursor_pos--;
		line->max_size--;
	}
	tputs(tgetstr("cd", NULL), 1, ft_pointchar);
	ft_putstr(line->line);
	line->cursor_pos = ft_strlen(line->line) + 2;
}

static void			print_cpy(int buf, t_edit *line)
{
	char		str[5];
	char		tmp[2];
	int			i = 0;

	str[0] = buf % 128;
	str[1] = buf >> 8;
	str[2] = buf >> 16;
	str[3] = buf >> 24;
	str[4] = '\0';
	while (str[i])
	{
		tmp[0] = str[i];
		tmp[1] = '\0';
		add_to_line(line, (int)str[i]);
		i++;
	}
}

static int				check_copy(int buf)
{
	char	check[4];
	int		i;

	i = 0;
	check[0] = buf % 128;
	check[1] = buf >> 8;
	check[2] = buf >> 16;
	check[3] = buf >> 24;
	while (i < 4)
	{
		if ((int)check[i] > 126 || (int)check[i] < 32)
			return (0);
		i++;
	}
	return (1);
}


void handle_key(int buf, t_edit *line)
{
	if (check_copy(buf))
		print_cpy(buf, line);
	else
	{
		if (buf == PRESS_LEFT)
			ft_left_arrow(line);
		else if (buf == PRESS_RIGHT)
			ft_right_arrow(line);
		else if (buf == PRESS_UP)
			ft_arrow_up(line);
		else if (buf == PRESS_DOWN)
			ft_arrow_down(line);
		// ft_putstr("OYO");
		if (!line->select_mode)
		{
			if (ft_isprint(buf))
				add_to_line(line, buf);
			else if (buf == PRESS_BACKSPACE)
				ft_delete(line);
			else if (buf == PRESS_SHIFT_LEFT)
				ft_wordleft(line);
			else if (buf == PRESS_SHIFT_RIGHT)
				ft_wordright(line);
			else if (buf == PRESS_HOME)
				ft_homekey(line);
			else if (buf == PRESS_END)
				ft_endkey(line);
		}
		else if (line->select_mode)
		{
			line->end_select = line->cursor_pos - 2;
			ft_go_start(line);
			ft_highlight(line);
		}
		if (buf == PRESS_ALT_C || buf == PRESS_ALT_V || buf == PRESS_ALT_X
		|| buf == PRESS_ALT_K)
			select_copy_cut(line, buf);
	}
}
