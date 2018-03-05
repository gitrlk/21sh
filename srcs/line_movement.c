/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:16:04 by jecarol           #+#    #+#             */
/*   Updated: 2018/03/05 18:41:49 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void ft_left_arrow(t_edit *line)
{
	if (line->cursor_pos >= 3)
	{
		line->cursor_pos--;
		ft_putstr("\033[1D");
	}
}

void ft_right_arrow(t_edit *line)
{
	if (line->cursor_pos < line->max_size)
	{
		line->cursor_pos++;
		ft_putstr("\033[1C");
	}
	if (((line->cursor_pos) % g_data->win_col) == 0)
	{
		tputs(tgetstr("do", NULL), 1, ft_pointchar);
		tputs(tgetstr("cr", NULL), 1, ft_pointchar);
	}
}

void ft_endkey(t_edit *line)
{
	while (line->cursor_pos < line->max_size)
	{
		ft_right_arrow(line);
	}
}

void ft_homekey(t_edit *line)
{
	while (line->cursor_pos > 2)
	{
		ft_left_arrow(line);
	}
}
