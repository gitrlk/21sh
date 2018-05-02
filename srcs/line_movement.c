/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:16:04 by jecarol           #+#    #+#             */
/*   Updated: 2018/05/02 14:15:22 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	ft_left_arrow(t_edit *line)
{
	int start;
	int up;

	if (line->cursor_pos == 2)
		return ;
	up = line->sz.ws_col;
	start = line->cursor_pos % line->sz.ws_col;
	if (start == 0)
	{
		ft_putstr_fd("\033[1A", STDOUT_FILENO);
		while (up > 0)
		{
			ft_putstr_fd("\033[1C", STDOUT_FILENO);
			up--;
		}

	}
	else
		ft_putstr_fd("\033[1D", STDOUT_FILENO);
	// }
	// if (line->prompt_mode == 0 && line->cursor_pos > 2)
	// {
	line->cursor_pos--;
	// 	ft_putstr_fd("\033[1D", STDOUT_FILENO);
	// }
	// if (line->cursor_pos > 2 && line->prompt_mode == 1)
	// {
	// 	line->cursor_pos--;
	// 	ft_putstr_fd("\033[1D", STDOUT_FILENO);
	// }
	// if (line->cur_mod_pos > 6 && line->prompt_mode == 2)
	// {
	// 	line->cur_mod_pos--;
	// 	ft_putstr_fd("\033[1D", STDOUT_FILENO);
	// }
}

void	ft_right_arrow(t_edit *line)
{
	if (line->cursor_pos == line->max_size)
		return ;
	if (line->prompt_mode == 0 && line->cursor_pos < line->max_size)
	{
		line->cursor_pos++;
		ft_putstr_fd("\033[1C", STDOUT_FILENO);
	}
	if ((line->cursor_pos % ((line->sz.ws_col)) == 0))
	{
		tputs(tgetstr("do", NULL), 1, ft_pointchar);
		tputs(tgetstr("cr", NULL), 1, ft_pointchar);
	}
}

void	ft_endkey(t_edit *line)
{
	if (line->prompt_mode == 0 || line->prompt_mode == 1)
		while (line->cursor_pos < line->max_size)
			ft_right_arrow(line);
	else
		while (line->cur_mod_pos < line->max_mod_size)
			ft_right_arrow(line);
}

void	ft_homekey(t_edit *line)
{
	if (line->prompt_mode == 0 || line->prompt_mode == 1)
		while (line->cursor_pos > 2)
			ft_left_arrow(line);
	else
		while (line->cur_mod_pos > 6)
			ft_left_arrow(line);
}
