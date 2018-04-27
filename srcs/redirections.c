/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:42:07 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/27 19:43:25 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			assign_redir(t_lexit *list, t_sh *sh)
{
	t_lexit		*tmp;

	tmp = list;
	while (tmp && tmp->prio != SEMICOLON)
	{
		if (tmp->prio == COMMAND)
			get_redir(tmp, sh);
		tmp = tmp->next;
	}
}

void			trim_and_free(t_lexit *save, t_lexit *tmp, t_lexit *to_free)
{
	save->next = tmp->next;
	tmp->next->prev = save;
	to_free = tmp;
	if (to_free)
		ft_strdel(&to_free->input);
	if (to_free->args[0])
		ft_freetab(to_free->args);
	free(tmp);
}

int				trim_end(t_lexit *tmp, t_lexit *save)
{
	if (tmp->input)
		ft_strdel(&tmp->input);
	if (tmp->args[0])
		ft_freetab(tmp->args);
	free(tmp);
	save->next = NULL;
	return (1);
}

void			trim_redir(t_lexit *list)
{
	t_lexit		*tmp;
	t_lexit		*save;
	t_lexit		*to_free;

	tmp = list;
	to_free = NULL;
	while (tmp)
	{
		if (tmp->prev && (tmp->prio == REDIR_R || tmp->prio == REDIR_RR ||
		tmp->prio == REDIR_L))
		{
			save = tmp->prev;
			while (tmp->next && tmp->prio != PIPE && tmp->prio != AND_OR &&
			tmp->prio != HEREDOC && tmp->prio != COMMAND &&
			tmp->prio != SEMICOLON)
			{
				trim_and_free(save, tmp, to_free);
				tmp = save->next;
			}
			if (!tmp->next)
				if (trim_end(tmp, save))
					break ;
		}
		tmp = tmp->next;
	}
}
