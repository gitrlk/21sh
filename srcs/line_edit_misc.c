/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit_misc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:11:24 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/27 20:41:27 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			ft_wordleft(t_edit *line)
{
	int			i;

	i = line->cursor_pos - 2;
	if (i > 0)
	{
		if (ft_isascii(line->line[i]))
		{
			if (line->line[i] == ' ')
				while (line->line[i] == ' ')
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

void			ft_wordright(t_edit *line)
{
	int			i;

	i = line->cursor_pos - 2;
	if (ft_isascii(line->line[i]))
	{
		if (line->line[i] == ' ')
			while (line->line[i] == ' ')
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

void			delete_std(t_edit *line, t_insert *vals)
{
	if ((line->cursor_pos == line->max_size) && (line->cursor_pos > 2))
	{
		vals->tmp = ft_strndup(line->line, ft_strlen(line->line) - 1);
		free(line->line);
		line->line = vals->tmp;
		ft_move_it(line, 0);
	}
	else if ((line->cursor_pos != line->max_size) && (line->cursor_pos > 2))
	{
		vals->tmp = ft_strndup(line->line, (line->cursor_pos - 3));
		vals->tmp2 = ft_strsub(line->line, (line->cursor_pos - 2),
				(ft_strlen(line->line) - line->cursor_pos) + 3);
		free(line->line);
		line->line = ft_freejoinstr(vals->tmp, vals->tmp2);
		ft_move_it(line, 0);
		while ((size_t)vals->i < ft_strlen(vals->tmp2))
		{
			ft_left_arrow(line);
			vals->i++;
		}
		ft_strdel(&vals->tmp2);
	}
}

void			ft_delete(t_edit *line)
{
	t_insert	vals;

	vals.i = 0;
	vals.tmp = NULL;
	vals.tmp2 = NULL;
	if (line->prompt_mode == 0 || line->prompt_mode == 1)
		delete_std(line, &vals);
	else if (line->prompt_mode == 2)
	{
		if ((line->cur_mod_pos == line->max_mod_size) &&
			(line->cur_mod_pos > 6))
		{
			vals.tmp = ft_strndup(line->q_str, ft_strlen(line->q_str) - 1);
			free(line->q_str);
			line->q_str = vals.tmp;
			ft_move_it(line, 0);
		}
	}
}

char			*get_quote_str(char *line)
{
	int			i;
	int			subber;
	char		*result;

	i = 0;
	subber = 0;
	result = NULL;
	while (line[i])
		i++;
	i--;
	while (line[i] && line[i] != '\n')
	{
		subber++;
		i--;
	}
	result = ft_strsub(line, i + 1, subber);
	return (result);
}
