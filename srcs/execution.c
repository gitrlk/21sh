#include "../includes/sh.h"


void				execute(t_sh *sh)
{

	if (check_if_builtin(sh->execs))
		exec_no_fork(sh->execs, sh->env, sh);
	else if (sh->execs->prio != ARG)
		execs(sh->execs, sh->env, sh);
	else
		ft_errors(6, NULL, sh->execs->args[0]);
}

void				execs_deep(t_lexit *list, t_env *env, t_sh *sh)
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

void				execs(t_lexit *list, t_env *env, t_sh *sh)
{
	if (list)
	{
		pid_t pid;
		int status;
		pid = fork();

		if (pid == 0)
			execs_deep(list, env, sh);
		else
			waitpid(pid, &status, 0);
	}
}

void				exec_no_fork(t_lexit *list, t_env *env, t_sh *sh)
{
	if (list)
		execs_deep(list, env, sh);
}

void				execute_builtin(t_lexit *list, t_env *env, t_sh *sh)
{
	int				mod;

	mod = 0;
	mod = switch_fd(list, sh, &mod);
	if (mod != -1)
	{
		if (!ft_strcmp(list->args[0], "env"))
			ft_env(list, env, sh);
		else if (!ft_strcmp(list->args[0], "echo"))
			ft_echo(list);
		else if (!ft_strcmp(list->args[0], "cd"))
			ft_cd(list->args, &env);
		else if (!ft_strcmp(list->args[0], "setenv"))
			exec_setenv((list->args + 1), &env);
		else if (!ft_strcmp(list->args[0], "unset"))
			exec_unsetenv((list->args + 1), &env);
		else if (!ft_strcmp(list->args[0], "exit"))
			exit (0);
		if (mod)
			reset_fd(sh, mod);
		if (list->is_pipe == 1)
			exit (0);
	}
}

void				execute_binary(t_lexit *list, t_env *env, t_sh *sh)
{
	char			**newenv;
	int			mod;

	mod = 0;
	newenv = ft_fill_envp(env);
	mod = switch_fd(list, sh, &mod);
	if (mod != -1)
	{
		execve(list->command, list->args, newenv);
		if (mod)
			reset_fd(sh, mod);
	}
	ft_freetab(newenv);
}

int				get_execs(t_sh *sh)
{
	t_execs		*igo;

	igo = init_igo(sh);
	if (check_semi(sh, igo->tmp))
	{
		while (igo->tmp)
		{
			cut_list(sh, igo);
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

// void swap_quote(t_execs *igo, t_sh *sh)
// {
// 	ft_putendl("SWAP QUOTE");
// 	if (sh->line->quote_complete)
// 	{
// 		ft_putendl("SWAP IN");
// 		while (igo->head->input && !ft_strchr(igo->head->input, '\''))
// 			igo->head = igo->head->next;
// 		if (igo->head->input && sh->line->quote_complete)
// 		{
// 				ft_strdel(&igo->head->input);
// 				ft_strdel(&igo->head->args[0]);
// 				igo->head->args[0] = sh->line->q_str;
// 				igo->head->input = sh->line->q_str;
// 		}
// 	}
// }

void				exec_segment(t_sh *sh, t_execs *igo)
{
	if (double_check(igo->head))
	{
		assign_redir(igo->head, sh);
		trim_redir(igo->head);
		// swap_quote(igo, sh);
		sh->execs = ft_tree_it(igo->head, NULL, 0);
		igo->tmp2 = sh->execs;
		execute(sh);
		while (igo->copy->first != 1)
			igo->copy = igo->copy->prev;
		free_list(igo->copy);
		sh->execs = NULL;
		igo->copy = NULL;
		igo->head = NULL;
		if (igo->tmp->next)
			igo->tmp = igo->tmp->next;
	}
}

void				exec_last_segment(t_sh *sh, t_execs *igo)
{
	if (double_check(igo->head))
	{
		assign_redir(igo->head, sh);
		trim_redir(igo->head);
		// swap_quote(igo, sh);
		sh->execs = ft_tree_it(igo->head, NULL, 0);
		execute(sh);
		while (igo->copy->first != 1)
			igo->copy = igo->copy->prev;
		free_list(igo->copy);
		igo->copy = NULL;
		sh->execs = NULL;
	}
}
