/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit_more.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:50 by jecarol           #+#    #+#             */
/*   Updated: 2018/04/25 19:35:32 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void				insert_std(t_insert *vals, int buf, t_edit *line)
{
	vals->tmp = ft_strndup(line->line, line->cursor_pos - 3);
	vals->tmp2 = ft_strsub(line->line, line->cursor_pos - 3 , (line->max_size - line->cursor_pos) + 1);
	ft_putchar_fd(buf, STDOUT_FILENO);
	vals->tmp3 = ft_freejoinstr(vals->tmp, vals->buf2);
	free(line->line);
	line->line = ft_freejoinstr(vals->tmp3, vals->tmp2);
	free(vals->tmp2);
	vals->tmp2 = ft_strsub(line->line, line->cursor_pos - 3 , (line->max_size - line->cursor_pos));
	ft_move_it(line, 1);
	while ((size_t)vals->i < ft_strlen(vals->tmp2))
	{
		ft_left_arrow(line);
		vals->i++;
	}
	free(vals->tmp2);
}

void				insert_hd(t_insert *vals, int buf, t_edit *line)
{
	vals->tmp = ft_strndup(line->q_str, line->cur_mod_pos - 7);
	vals->tmp2 = ft_strsub(line->q_str, line->cur_mod_pos - 7 , (line->max_mod_size - line->cur_mod_pos) + 1);
	ft_putchar_fd(buf, STDOUT_FILENO);
	vals->tmp3 = ft_freejoinstr(vals->tmp, vals->buf2);
	free(line->q_str);
	line->q_str = ft_freejoinstr(vals->tmp3, vals->tmp2);
	free(vals->tmp2);
	vals->tmp2 = ft_strsub(line->q_str, line->cur_mod_pos - 7 , (line->max_mod_size - line->cur_mod_pos));
	ft_move_it(line, 1);
	while ((size_t)vals->i < ft_strlen(vals->tmp2))
	{
		ft_left_arrow(line);
		vals->i++;
	}
	free(vals->tmp2);
}

void ft_insert(int buf, t_edit *line)
{
	t_insert		vals;

	vals.buf2[0] = (char)buf;
	vals.buf2[1] = '\0';
	vals.i = 0;
	vals.tmp = NULL;
	vals.tmp2 = NULL;
	vals.tmp3 = NULL;
	if (line->prompt_mode == 0 || line->prompt_mode == 1)
		insert_std(&vals, buf, line);
	else
		insert_hd(&vals, buf, line);
}

void				add_to_line_std(t_edit *line, int buf, char *buf2)
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

void add_to_line(t_edit *line, int buf)
{
	char buf2[2];

	buf2[0] = (char)buf;
	buf2[1] = '\0';
	if (line->prompt_mode == 0 || line->prompt_mode == 1)
		add_to_line_std(line, buf, buf2);
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
