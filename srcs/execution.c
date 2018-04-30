/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:16:06 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/30 18:09:42 by rlkcmptr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void				execute(t_sh *sh)
{
	if (check_if_builtin(sh->execs))
		exec_no_fork(sh->execs, &sh->env, sh);
	else if (sh->execs->prio != ARG)
		execs(sh->execs, &sh->env, sh);
	else if (sh->execs->prio == ARG)
		ft_errors(6, NULL, sh->execs->args[0]);
}

void				execs_deep(t_lexit *list, t_env **env, t_sh *sh)
{
	if (list->prio == PIPE)
		do_pipes(list, env, sh);
	if (list->left)
		execs_deep(list->left, env, sh);
	if (list->prio == COMMAND)
	{
		if (check_if_builtin(list))
			execute_builtin(list, env, sh);
		else
			execute_binary(list, env, sh);
	}
	if (list->right)
		execs_deep(list->right, env, sh);
}

void				execs(t_lexit *list, t_env **env, t_sh *sh)
{
	pid_t			pid;
	int				status;

	if (list)
	{
		pid = fork();
		if (pid == 0)
			execs_deep(list, env, sh);
		else
			waitpid(pid, &status, 0);
	}
}

void				exec_no_fork(t_lexit *list, t_env **env, t_sh *sh)
{
	if (list)
		execs_deep(list, env, sh);
}

void				exec_last_segment(t_sh *sh, t_execs *igo)
{
	t_lexit			*tete;

	tete = igo->head;
	if (double_check(igo->head))
	{
		assign_redir(igo->head, sh);
		trim_redir(igo->head);
		sh->execs = ft_tree_it(igo->head, NULL, 0);
		execute(sh);
		free_list(tete);
		igo->copy = NULL;
		sh->execs = NULL;
	}
}
