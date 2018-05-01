/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:14:55 by jecarol           #+#    #+#             */
/*   Updated: 2018/05/01 19:14:06 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int				check_if_builtin(t_lexit *list)
{
	if (list)
	{
		if (list->args && (!ft_strcmp(list->args[0], "env") ||
					!ft_strcmp(list->args[0], "echo") ||
		!ft_strcmp(list->args[0], "cd") || !ft_strcmp(list->args[0], "exit")
		|| !ft_strcmp(list->args[0], "setenv")
		|| !ft_strcmp(list->args[0], "unset")))
			return (1);
		return (0);
	}
	else
		return (0);
}

void			kick_semi(t_lexit *list)
{
	t_lexit		*tmp;
	tmp = list;
	while (tmp)
	{
		if (tmp->prio == SEMICOLON && !tmp->next)
		{
			if (tmp->input)
				ft_strdel(&tmp->input);
			if (tmp->args[0])
				ft_freetab(tmp->args);
			tmp->prev->next = NULL;
			free(tmp);
			tmp = NULL;
			// tmp->prev->next = NULL;
		}
		else
			tmp = tmp->next;
	}
}

void			parsing_exing(t_sh *sh)
{
	if (double_check(sh->list))
	{
		assign_redir(sh->list, sh);
		trim_redir(sh->list);
		kick_semi(sh->list);
		sh->execs = ft_tree_it(sh->list, NULL, 0);
		if (sh->execs && sh->execs->args)
			execute(sh);
		free_list(sh->list);
		sh->list = NULL;
		if (sh->hd_state)
			ft_strdel(&sh->hd_state);
	}
}

void			p_l_x(t_sh *sh)
{
	int			i;
	int			number;

	i = 0;
	number = 0;
	if (parsing_listing(&sh->list, sh->env, sh))
	{
		number = get_execs(sh);
		if (number == 1)
			if (sh->list)
				parsing_exing(sh);
	}
	if (sh->list)
	{
		free_list(sh->list);
		sh->list = NULL;
	}
	if (sh->hd_state)
		ft_strdel(&sh->hd_state);
}

void			ft_21sh(t_sh *sh)
{
	int			ret;

	ft_prompt(1);
	init_term();
	sh->buf = 0;
	ret = 0;
	while ((ret = read(0, &sh->buf, sizeof(int))) &&
	sh->buf != '\n')
	{
		handle_key(sh);
		sh->buf = 0;
	}
	ft_endkey(sh->line);
	ft_add_history(sh->line);
	ft_putchar('\n');
	set_term_back();
	p_l_x(sh);
	if (ft_strequ(sh->line->line, "clear"))
		tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	ft_line_reset(sh->line);
}

int				main(int ac, char **av, char **envp)
{
	t_sh		*sh;
	int			i;

	(void)ac;
	(void)av;
	i = 0;
	if (ac != 1)
		return (0);
	sh = ft_memalloc(sizeof(t_sh));
	sh->line = ft_memalloc(sizeof(t_edit));
	init_structs(sh->line, &sh->fd);
	listen_signal();
	while (envp[i])
		ft_push_env(&sh->env, envp[i++]);
	while (42)
		ft_21sh(sh);
	return (0);
}
