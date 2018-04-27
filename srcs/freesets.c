/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freesets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:03 by jecarol           #+#    #+#             */
/*   Updated: 2018/04/27 02:54:52 by rlkcmptr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			ft_freetab(char **table)
{
	int			i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
	{
		ft_strdel((&table[i]));
		i++;
	}
	if (table)
		ft_memdel((void **)&table);
}

void			ft_line_reset(t_edit *line)
{
	ft_strdel(&line->line);
	free(line->line);
	line->cursor_pos = 2;
	line->max_size = 2;
	line->line = ft_memalloc(sizeof(char));
	line->select_mode = 0;
	line->curr = NULL;
}

void			clean_list(t_lexit *tmp)
{
	if (tmp->input)
		ft_strdel(&tmp->input);
	if (tmp->args)
		ft_freetab(tmp->args);
	if (tmp->command)
		ft_strdel(&tmp->command);
	if (tmp->checker && tmp->redirs->right_target)
		ft_strdel(&tmp->redirs->right_target);
	if (tmp->checker && tmp->redirs->left_target)
	{
		ft_strdel(&tmp->redirs->left_target);
		if (tmp->redirs->redir_left == 2)
			ft_strdel(&tmp->redirs->endoff);
	}
}

void			free_list(t_lexit *list)
{
	t_lexit		*tmp;
	int			checker;

	checker = 0;
	tmp = list;
	if (tmp)
	{
		while(list)
		{
			tmp = list;
			list = list->next;
			clean_list(tmp);
				free(tmp->redirs);
			if (tmp)
				free(tmp);
		}
	}
}

int				free_igo(t_execs *igo, int mod)
{
	int			exec_number;

	exec_number = igo->exec_number;
	if (mod == 1)
	{
		free(igo);
		return (1);
	}
	else
	{
		free(igo);
		return (exec_number);
	}
}
