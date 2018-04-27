/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:58 by jecarol           #+#    #+#             */
/*   Updated: 2018/04/27 03:01:28 by rlkcmptr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			sig_trap(t_edit *line, int buf)
{
	if (buf == 3)
	{
		if (line->prompt_mode == 2)
			ft_strdel(&line->q_str);
		ft_line_reset(line);
		tputs(tgetstr("cd", NULL), 1, ft_pointchar);
		if (line->prompt_mode == 0)
		{
			ft_putchar('\n');
			ft_prompt(1);
		}
		else
			line->prompt_mode = 0;
	}
	else if (((line->max_mod_size == 6) || (line->max_size == 2)) &&
			(line->prompt_mode == 0) && buf == 4)
	{
		ft_strdel(&line->line);
		ft_strdel(&line->q_str);
		free(line->line);
		set_term_back();
		exit(0);
	}
}

void			select_mode_off(t_sh *sh)
{
	if (ft_isprint(sh->buf))
		add_to_line(sh->line, sh->buf);
	else if (sh->buf == PRESS_BACKSPACE)
		ft_delete(sh->line);
	else if (sh->buf == PRESS_SHIFT_LEFT)
		ft_wordleft(sh->line);
	else if (sh->buf == PRESS_SHIFT_RIGHT)
		ft_wordright(sh->line);
	else if (sh->buf == PRESS_HOME)
		ft_homekey(sh->line);
	else if (sh->buf == PRESS_END)
		ft_endkey(sh->line);
}

void 			select_mode_on(t_sh *sh)
{
	sh->line->end_select = sh->line->cursor_pos - 2;
	ft_go_start(sh->line);
	ft_highlight(sh->line);
}


void			handle_key(t_sh *sh)
{
	if (check_copy(sh->buf))
		print_cpy(sh->buf, sh->line);
	else
	{
		if (sh->buf == 3 || sh->buf == 4)
			sig_trap(sh->line, sh->buf);
		if (sh->buf == PRESS_LEFT && sh->line->prompt_mode != 2 &&
				!sh->line->select_mode)
			ft_left_arrow(sh->line);
		else if (sh->buf == PRESS_RIGHT)
			ft_right_arrow(sh->line);
		else if (sh->buf == PRESS_UP && sh->line->prompt_mode == 0)
			ft_arrow_up(sh->line);
		else if (sh->buf == PRESS_DOWN && sh->line->prompt_mode == 0)
			ft_arrow_down(sh->line);
		if (!sh->line->select_mode)
			select_mode_off(sh);
		else if (sh->line->select_mode)
			select_mode_on(sh);
		if (sh->buf == PRESS_ALT_C || sh->buf == PRESS_ALT_V ||
				sh->buf == PRESS_ALT_X
				|| sh->buf == PRESS_ALT_K)
			select_copy_cut(sh->line, sh->buf);
	}
}
