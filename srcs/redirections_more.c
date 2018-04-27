/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_more.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:38:42 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/27 20:38:33 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void				get_std_src_dst(t_lexit *node)
{
	if (node->args && ft_isdigit(node->args[0][0]))
		node->prev->fdsrc = ft_atoi(node->args[0]);
	if (node->next && node->next->args)
	{
		if (node->next->args[0][0] == '-')
			node->prev->fdclose = 1;
		if (ft_isdigit(node->next->args[0][0]))
			node->prev->fddst = ft_atoi(node->next->args[0]);
	}
}

void				last_right_redir(t_lexit *node, t_lexit *tmp)
{
	node->prev->redirs->redir_right = tmp->prio == REDIR_R ? 1 : 2;
	if (node->prev->redirs->right_target)
		ft_strdel(&node->prev->redirs->right_target);
	node->prev->redirs->right_target = ft_strdup(tmp->next->input);
	get_std_src_dst(node);
}

void				last_left_redir(t_lexit *node, t_lexit *tmp, t_sh *sh)
{
	node->prev->redirs->redir_left = tmp->prio == REDIR_L ? 1 : 2;
	if (tmp->prio == HEREDOC)
		get_eof(tmp, sh);
	if (node->prev->redirs->left_target)
		ft_strdel(&node->prev->redirs->left_target);
	node->prev->redirs->left_target = ft_strdup(tmp->next->input);
}

void				get_last_redir(t_lexit *node, t_sh *sh)
{
	t_lexit		*tmp;

	tmp = node;
	init_redirs(node->prev);
	while (tmp && (tmp->prio != SEMICOLON && tmp->prio != AND_OR && tmp->prio !=
	PIPE && tmp->prio != COMMAND))
	{
		if (tmp->next && ((tmp->prio == REDIR_R || tmp->prio == REDIR_RR)))
			last_right_redir(node, tmp);
		if (tmp->next && ((tmp->prio == REDIR_L || tmp->prio == HEREDOC)))
			last_left_redir(node, tmp, sh);
		tmp = tmp->next;
	}
}

void				get_redir(t_lexit *node, t_sh *sh)
{
	t_lexit			*tmp;

	tmp = node;
	if (tmp->next && (tmp->next->prio == REDIR_R ||
		tmp->next->prio == REDIR_L || tmp->next->prio == REDIR_RR ||
		tmp->next->prio == HEREDOC))
		get_last_redir(tmp->next, sh);
}
