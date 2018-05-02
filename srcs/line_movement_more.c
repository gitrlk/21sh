/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_movement_more.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:01:42 by jecarol           #+#    #+#             */
/*   Updated: 2018/05/02 16:01:43 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void	ft_left_arrow_q(t_edit *line)
{
	int start;
	int up;

	if (line->cur_mod_pos == 6)
		return ;
	up = line->sz.ws_col;
	start = line->cur_mod_pos % line->sz.ws_col;
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
	line->cur_mod_pos--;
}

void	ft_right_arrow_q(t_edit *line)
{
	if (line->cur_mod_pos == line->max_mod_size)
		return ;
	if (line->prompt_mode == 1 && line->cur_mod_pos < line->max_mod_size)
	{
		line->cur_mod_pos++;
		ft_putstr_fd("\033[1C", STDOUT_FILENO);
	}
	if ((line->cur_mod_pos % ((line->sz.ws_col)) == 0))
	{
		tputs(tgetstr("do", NULL), 1, ft_pointchar);
		tputs(tgetstr("cr", NULL), 1, ft_pointchar);
	}
}
