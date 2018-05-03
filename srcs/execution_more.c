/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_more.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:17:42 by rfabre            #+#    #+#             */
/*   Updated: 2018/05/03 15:38:26 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		exec_env(t_lexit *list, int i, t_env *new_env, t_sh *sh)
{
	update_list(list, i, new_env);
	if (check_if_builtin(list))
		exec_no_fork(list, &new_env, sh);
	else if (list->prio != ARG)
		execs(sh->execs, &new_env, sh);
	else
		ft_errors(7, NULL, sh->execs->args[0]);
}

void		execute_builtin(t_lexit *list, t_env **env, t_sh *sh)
{
	int		mod;

	mod = 0;
	mod = switch_fd(list, sh, &mod);
	if (mod != -1)
	{
		if (!ft_strcmp(list->args[0], "env"))
			ft_env(list, env, sh);
		else if (!ft_strcmp(list->args[0], "echo"))
			ft_echo(list, env);
		else if (!ft_strcmp(list->args[0], "cd"))
			ft_cd(list->args, env);
		else if (!ft_strcmp(list->args[0], "setenv"))
			exec_setenv((list->args + 1), env);
		else if (!ft_strcmp(list->args[0], "unset"))
			exec_unsetenv((list->args + 1), env);
		else if (!ft_strcmp(list->args[0], "exit"))
			exit(0);
		if (mod)
			reset_fd(sh, mod);
		if (list->is_pipe == 1)
			exit(0);
	}
}

void		execute_binary(t_lexit *list, t_env **env, t_sh *sh)
{
	char	**newenv;
	int		mod;

	mod = 0;
	newenv = ft_fill_envp(*env);
	mod = switch_fd(list, sh, &mod);
	if (mod != -1)
	{
		execve(list->command, list->args, newenv);
		if (mod)
			reset_fd(sh, mod);
	}
	ft_freetab(newenv);
}

int			get_execs(t_sh *sh)
{
	t_execs	*igo;

	igo = init_igo(sh);
	if (check_semi(sh, igo->tmp))
	{
		while (igo->tmp)
		{
			cut_list(igo);
			if (igo->tmp->next && igo->tmp->next->prio == SEMICOLON)
				exec_segment(sh, igo);
			if (igo->tmp->prio != SEMICOLON && !igo->tmp->next)
				exec_last_segment(sh, igo);
			igo->tmp = igo->tmp->next;
		}
		return (free_igo(igo, 2));
	}
	else
		return (free_igo(igo, 1));
}

void		exec_segment(t_sh *sh, t_execs *igo)
{
	t_lexit	*tete;

	tete = igo->head;
	if (double_check(igo->head))
	{
		assign_redir(igo->head, sh);
		trim_redir(igo->head);
		sh->execs = ft_tree_it(igo->head, NULL, 0);
		igo->tmp2 = sh->execs;
		execute(sh);
		free_list(tete);
		lol(sh, igo);
		if (igo->tmp->next)
			igo->tmp = igo->tmp->next;
	}
	else
	{
		free_list(tete);
		lol(sh, igo);
		if (igo->tmp->next)
			igo->tmp = igo->tmp->next;
	}
}
