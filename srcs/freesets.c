/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freesets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:03 by jecarol           #+#    #+#             */
/*   Updated: 2018/03/05 18:41:23 by rfabre           ###   ########.fr       */
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
	ft_memdel((void **)&table);
}

void			ft_line_reset(t_edit *line)
{
	ft_strdel(&line->line);
	free(line->line);
	ft_strdel(&g_data->line);
	line->cursor_pos = 2;
	line->max_size = 2;
	line->line = ft_memalloc(sizeof(char));
	g_data->line = ft_memalloc(sizeof(char));
	line->select_mode = 0;
	line->curr = NULL;
}

void 				ft_free_lexdat(t_lexit *lexdat)
{
	t_lexit *tmp;

	tmp = lexdat;
	while (lexdat)
	{
		tmp = lexdat;
		lexdat = lexdat->next;
		ft_strdel(&tmp->input);
		ft_freetab(tmp->to_exec);
		ft_freetab(tmp->allpaths);
		free(tmp);
	}
}
