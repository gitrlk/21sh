/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 17:40:18 by rfabre            #+#    #+#             */
/*   Updated: 2018/05/03 01:32:25 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int				check_semi(t_sh *sh, t_lexit *lst)
{
	t_lexit		*tmp;
	int			i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		if (tmp->next && tmp->prio == SEMICOLON)
			return (1);
		if (!tmp->next)
		{
			sh->execs = sh->list;
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int				check_pipe(t_lexit *node, int checker)
{
	if (!node->prev && !node->next)
		return (ft_errors(6, NULL, node->args[0]));
	if (!checker)
	{
		if (node->prev->prio != COMMAND || node->next->prio != COMMAND)
			return (node->prev->prio != COMMAND ?
					ft_errors(6, NULL, node->prev->args[0]) :
					ft_errors(6, NULL, node->next->args[0]));
	}
	else if (checker == 1)
	{
		if (node->next->prio != COMMAND)
			return (ft_errors(6, NULL, node->next->args[0]));
	}
	return (1);
}

int				check_redirr(t_lexit *node, int checker)
{
	if (!node->prev)
		return (ft_errors(6, NULL, node->args[0]));
	if (!checker)
		return (ft_errors(6, NULL, node->prev->args[0]));
	return (1);
}

int				check_redirl(t_lexit *node)
{
	if (!node->prev || !node->next)
		return (ft_errors(6, NULL, node->args[0]));
	if (node->prio == HEREDOC)
	{
		if (node->prev->prio != COMMAND)
			return (ft_errors(6, NULL, node->prev->args[0]));
	}
	else if ((open(node->next->args[0], O_RDONLY)) == -1)
		return (ft_errors(4, NULL, node->next->args[0]));
	return (1);
}

int				double_check(t_lexit *lst)
{
	int			checker;
	t_lexit		*tmp;

	checker = 0;
	tmp = lst;
	if (tmp)
	{
		while (tmp)
		{
			if (tmp->prio == COMMAND)
				checker = 1;
			if (tmp->prio == PIPE)
				if (!check_pipe(tmp, checker))
					return (0);
			if (tmp->prio == REDIR_R || tmp->prio == REDIR_RR)
				if (!check_redirr(tmp, checker))
					return (0);
			if (tmp->prio == REDIR_L || tmp->prio == HEREDOC)
				if (!check_redirl(tmp))
					return (0);
			tmp = tmp->next;
		}
		return (1);
	}
	return (0);
}
