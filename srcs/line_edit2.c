/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:50 by jecarol           #+#    #+#             */
/*   Updated: 2018/02/26 20:15:51 by jecarol          ###   ########.fr       */
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
	tmp = ft_strndup(line->line, line->cursor_pos - 3);
	tmp2 = ft_strsub(line->line, line->cursor_pos - 3 , line->max_size);
	ft_putchar(buf);
	tmp3 = ft_freejoinstr(tmp, buf2);
	free(line->line);
	line->line = ft_freejoinstr(tmp3, tmp2);
	free(tmp2);
	tmp2 = ft_strsub(line->line, line->cursor_pos - 2 , line->max_size);
	ft_move_it(line, 1);
	while ((size_t)i < ft_strlen(tmp2))
	{
		ft_left_arrow(line);
		i++;
	}
	free(tmp2);
}

void add_to_line(t_edit *line, int buf)
{
	char buf2[2];

	buf2[0] = (char)buf;
	buf2[1] = '\0';
	line->max_size++;
	line->cursor_pos++;
	if (line->cursor_pos == line->max_size)
	{
		line->line = ft_freejoinstr(line->line, buf2);
		ft_putchar(buf);
	}
	else if (line->cursor_pos != line->max_size)
		ft_insert(buf, line);
}
