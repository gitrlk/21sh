/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freesets.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:03 by jecarol           #+#    #+#             */
/*   Updated: 2018/03/08 20:35:50 by jecarol          ###   ########.fr       */
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
	line->cursor_pos = 2;
	line->max_size = 2;
	line->line = ft_memalloc(sizeof(char));
	line->select_mode = 0;
	line->curr = NULL;
	ft_freetab(line->line_split);
}

void 				ft_free_lexdat(t_lexit *lexdat)
{
	if (!lexdat)
		return ;
	ft_free_lexdat(lexdat->left);
	ft_free_lexdat(lexdat->right);
	ft_strdel(&lexdat->input);
	free(lexdat->next);
	free(lexdat);
}
