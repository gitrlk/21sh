/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:58 by jecarol           #+#    #+#             */
/*   Updated: 2018/04/25 20:12:13 by jecarol          ###   ########.fr       */
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

void				delete_std(t_edit *line, t_insert *vals)
{
	if ((line->cursor_pos == line->max_size) && (line->cursor_pos > 2))
	{
		vals->tmp = ft_strndup(line->line, ft_strlen(line->line) - 1);
		free (line->line);
		line->line = vals->tmp;
		ft_move_it(line, 0);
	}
	else if ((line->cursor_pos != line->max_size) && (line->cursor_pos > 2))
	{
		vals->tmp = ft_strndup(line->line, (line->cursor_pos - 3));
		vals->tmp2 = ft_strsub(line->line, (line->cursor_pos - 2),
				(ft_strlen(line->line) - line->cursor_pos) + 3);
		free (line->line);
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

void ft_delete(t_edit *line)
{
	t_insert		vals;

	vals.i = 0;
	vals.tmp = NULL;
	vals.tmp2 = NULL;
	if (line->prompt_mode == 0 || line->prompt_mode == 1)
		delete_std(line, &vals);
	else if (line->prompt_mode == 2)
	{
		if ((line->cur_mod_pos == line->max_mod_size) && (line->cur_mod_pos > 6))
		{
			vals.tmp = ft_strndup(line->q_str, ft_strlen(line->q_str) - 1);
			free (line->q_str);
			line->q_str = vals.tmp;
			ft_move_it(line, 0);
		}
	}
}

char	*get_quote_str(char *line)
{
	int i;
	int subber;
	char *result;

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
	result = ft_strsub(line, i+1, subber);
	return (result);
}

void		std_move_it(t_insert *vals, t_edit *line, int check)
{
		while (vals->i < line->max_size)
		{
			ft_left_arrow(line);
			vals->i++;
		}
		if (check == 0)
		{
			line->cursor_pos--;
			line->max_size--;
		}
		ft_putstr_fd(line->line, STDOUT_FILENO);
		line->cursor_pos = ft_strlen(line->line) + 2;
		tputs(tgetstr("cd", NULL), 1, ft_pointchar);
}

void ft_move_it(t_edit *line, int check)
{
	t_insert		vals;

	vals.i = 0;
	vals.tmp = NULL;
	if (line->prompt_mode == 0 || line->prompt_mode == 1)
		std_move_it(&vals, line, check);
	else if (line->prompt_mode == 2)
	{
		while (vals.i < (line->max_mod_size - 6))
		{
			ft_left_arrow(line);
			vals.i++;
		}
		tputs(tgetstr("cd", NULL), 1, ft_pointchar);
		if (check == 0)
		{
			line->cur_mod_pos--;
			line->max_mod_size--;
		}
		vals.tmp = get_quote_str(line->q_str);
		ft_putstr_fd(vals.tmp, STDOUT_FILENO);
		line->cur_mod_pos = ft_strlen(vals.tmp) + 6;
		line->max_mod_size = ft_strlen(vals.tmp) + 6;
		ft_strdel(&vals.tmp);
	}
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

void sig_trap(t_edit *line, int buf)
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


void handle_key(t_sh *sh)
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
