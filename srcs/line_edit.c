/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:58 by jecarol           #+#    #+#             */
/*   Updated: 2018/04/23 03:17:47 by rlkcmptr         ###   ########.fr       */
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

void ft_delete(t_edit *line)
{
	char *tmp;
	char *tmp2;
	int i;

	i = 0;
	if (line->prompt_mode == 0 || line->prompt_mode == 1)
	{
		if ((line->cursor_pos == line->max_size) && (line->cursor_pos > 2))
		{
			tmp = ft_strndup(line->line, ft_strlen(line->line) - 1);
			free (line->line);
			line->line = tmp;
			ft_move_it(line, 0);
		}
		else if ((line->cursor_pos != line->max_size) && (line->cursor_pos > 2))
		{
			tmp = ft_strndup(line->line, (line->cursor_pos - 3));
			tmp2 = ft_strsub(line->line, (line->cursor_pos - 2),
					(ft_strlen(line->line) - line->cursor_pos) + 3);
			free (line->line);
			line->line = ft_freejoinstr(tmp, tmp2);
			ft_move_it(line, 0);
			while ((size_t)i < ft_strlen(tmp2))
			{
				ft_left_arrow(line);
				i++;
			}
		}
	}
	else if (line->prompt_mode == 2)
	{
		if ((line->cur_mod_pos == line->max_mod_size) && (line->cur_mod_pos > 6))
		{
			tmp = ft_strndup(line->q_str, ft_strlen(line->q_str) - 1);
			free (line->q_str);
			line->q_str = tmp;
			// while ((size_t)i < ft_strlen(tmp2))
			// {
			// 	ft_left_arrow(line);
			// 	i++;
			// }
			ft_move_it(line, 0);
		}
		// else if ((line->cur_mod_pos != line->max_mod_size) && (line->cur_mod_pos > 6))
		// {
		// 	tmp = ft_strndup(line->q_str, (line->cursor_pos - 7));
		// 	tmp2 = ft_strsub(line->q_str, (line->cursor_pos - 6),
		// 			(ft_strlen(line->q_str) - line->cursor_pos) + 7);
		// 	free (line->q_str);
		// 	line->q_str = ft_freejoinstr(tmp, tmp2);
		// 	ft_putstr("c ici ksa part en couillers --- \n");
		// 	ft_putendl(line->q_str);
		// 	ft_putstr("-------------------------------- \n");
		// 	ft_move_it(line, 0);
		// 	while ((size_t)i < ft_strlen(tmp2))
		// 	{
		// 		ft_left_arrow(line);
		// 		i++;
		// 	}
		// }
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

void ft_move_it(t_edit *line, int check)
{
	int i;
	char *tmp;

	tmp = NULL;
	i = 0;
	// tputs(tgetstr("cd", NULL), 1, ft_pointchar);
	if (line->prompt_mode == 0 || line->prompt_mode == 1)
	{
		while (i < line->max_size)
		{
			ft_left_arrow(line);
			i++;
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
	else if (line->prompt_mode == 2)
	{
		while (i < (line->max_mod_size - 6))
		{
			ft_left_arrow(line);
			i++;
		}
		tputs(tgetstr("cd", NULL), 1, ft_pointchar);
		if (check == 0)
		{
			line->cur_mod_pos--;
			line->max_mod_size--;
		}
		tmp = get_quote_str(line->q_str);
		ft_putstr_fd(tmp, STDOUT_FILENO);
		line->cur_mod_pos = ft_strlen(tmp) + 6;
		line->max_mod_size = ft_strlen(tmp) + 6;
		ft_strdel(&tmp);
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

void sig_trap(t_edit *line, int buf, int mode)
{
		if (buf == 3)
		{
			ft_strdel(&line->line);
			free(line->line);
			line->cursor_pos = 2;
			line->max_size = 2;
			line->line = ft_memalloc(sizeof(char));
			line->select_mode = 0;
			line->curr = NULL;
			tputs(tgetstr("cd", NULL), 1, ft_pointchar);
			if (!mode)
			{
				ft_putchar('\n');
				ft_prompt(1);
			}
			else
				line->prompt_mode = 0;
		}
		if (buf == 4)
		{
			ft_strdel(&line->line);
			free(line->line);
			set_term_back();
			exit(0);
		}
}

void handle_key(t_sh *sh)
{
	if (check_copy(sh->buf))
		print_cpy(sh->buf, sh->line);
	else
	{
		if (sh->buf == 3 || ((sh->buf == 4) && (sh->line->max_size == 2)) || ((sh->buf == 4) && (sh->line->cur_mod_pos == 6)))
			sig_trap(sh->line, sh->buf, sh->line->prompt_mode);
		if (sh->buf == PRESS_LEFT && sh->line->prompt_mode != 2)
			ft_left_arrow(sh->line);
		else if (sh->buf == PRESS_RIGHT)
			ft_right_arrow(sh->line);
		else if (sh->buf == PRESS_UP)
			ft_arrow_up(sh->line);
		else if (sh->buf == PRESS_DOWN)
			ft_arrow_down(sh->line);
		if (!sh->line->select_mode)
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
		else if (sh->line->select_mode)
		{
			sh->line->end_select = sh->line->cursor_pos - 2;
			ft_go_start(sh->line);
			ft_highlight(sh->line);
		}
		if (sh->buf == PRESS_ALT_C || sh->buf == PRESS_ALT_V || sh->buf == PRESS_ALT_X
		|| sh->buf == PRESS_ALT_K)
			select_copy_cut(sh->line, sh->buf);
	}
}
