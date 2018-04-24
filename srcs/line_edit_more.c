/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit_more.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:50 by jecarol           #+#    #+#             */
/*   Updated: 2018/04/24 21:21:06 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void ft_insert(int buf, t_edit *line)
{
	char *tmp;
	char *tmp2;
	char *tmp3;
	char buf2[2];
	int i;

	buf2[0] = (char)buf;
	buf2[1] = '\0';
	i = 0;
	if (line->prompt_mode == 0 || line->prompt_mode == 1)
	{
		tmp = ft_strndup(line->line, line->cursor_pos - 3);
		tmp2 = ft_strsub(line->line, line->cursor_pos - 3 , (line->max_size - line->cursor_pos) + 1);
		ft_putchar_fd(buf, STDOUT_FILENO);
		tmp3 = ft_freejoinstr(tmp, buf2);
		free(line->line);
		line->line = ft_freejoinstr(tmp3, tmp2);
		free(tmp2);
		tmp2 = ft_strsub(line->line, line->cursor_pos - 3 , (line->max_size - line->cursor_pos));
		ft_move_it(line, 1);
		while ((size_t)i < ft_strlen(tmp2))
		{
			ft_left_arrow(line);
			i++;
		}
		free(tmp2);
	}
	else
	{
		tmp = ft_strndup(line->q_str, line->cur_mod_pos - 7);
		tmp2 = ft_strsub(line->q_str, line->cur_mod_pos - 7 , (line->max_mod_size - line->cur_mod_pos) + 1);
		ft_putchar_fd(buf, STDOUT_FILENO);
		tmp3 = ft_freejoinstr(tmp, buf2);
		free(line->q_str);
		line->q_str = ft_freejoinstr(tmp3, tmp2);
		free(tmp2);
		tmp2 = ft_strsub(line->q_str, line->cur_mod_pos - 7 , (line->max_mod_size - line->cur_mod_pos));
		ft_move_it(line, 1);
		while ((size_t)i < ft_strlen(tmp2))
		{
			ft_left_arrow(line);
			i++;
		}
		free(tmp2);
	}

}

void add_to_line(t_edit *line, int buf)
{
	char buf2[2];

	buf2[0] = (char)buf;
	buf2[1] = '\0';
	if (line->prompt_mode == 0 || line->prompt_mode == 1)
	{
		line->max_size++;
		line->cursor_pos++;
		if (line->cursor_pos == line->max_size)
		{
			line->line = ft_freejoinstr(line->line, buf2);
			ft_putchar_fd(buf, STDOUT_FILENO);
		}
		else if (line->cursor_pos != line->max_size)
			ft_insert(buf, line);
	}
	else if (line->prompt_mode == 2)
	{
		line->max_mod_size++;
		line->cur_mod_pos++;
		if (line->cur_mod_pos == line->max_mod_size)
		{
			line->q_str = ft_freejoinstr(line->q_str, buf2);
			ft_putchar_fd(buf, STDOUT_FILENO);
		}
		else if (line->cur_mod_pos != line->max_mod_size)
			ft_insert(buf, line);
	}
}
