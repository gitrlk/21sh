/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 20:09:29 by rfabre            #+#    #+#             */
/*   Updated: 2018/01/25 22:51:58 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void ft_insert(char *buf, t_edit *line)
{
	char *tmp;
	char *tmp2;
	char *tmp3;
	int i;

	i = 0;
	tmp = ft_strndup(line->line, line->cursor_pos - 3);
	tmp2 = ft_strsub(line->line, line->cursor_pos - 3 , line->max_size);
	ft_putchar(buf[0]);
	tmp3 = ft_freejoinstr(tmp, buf);
	free(line->line);
	line->line = ft_freejoinstr(tmp3, tmp2);
	free(tmp2);
	tmp2 = ft_strsub(line->line, line->cursor_pos - 2 , line->max_size);
	ft_move_it(line, buf, 1);
	while ((size_t)i < ft_strlen(tmp2))
	{
		buf[2] = 68;
		ft_left_arrow(buf, line);
		i++;
	}
	free(tmp2);
}

void add_to_line(t_edit *line,char *buf)
{
  line->max_size++;
  line->cursor_pos++;
  if (line->cursor_pos == line->max_size)
  {
    line->line = ft_freejoinstr(line->line, buf);
    ft_putchar(buf[0]);
  }
  else if (line->cursor_pos != line->max_size)
		ft_insert(buf, line);
}
