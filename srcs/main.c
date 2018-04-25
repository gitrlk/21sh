/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:14:55 by jecarol           #+#    #+#             */
/*   Updated: 2018/04/25 20:58:47 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char			**copypasta(char **src, int i)
{
	int			size;
	int			j;
	char		**ret;

	size = 0;
	j = 0;
	while (src[size])
		size++;
	if (!(ret = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (src[i])
	{
		ret[j] = ft_strdup(src[i]);
		i++;
		j++;
	}
	ret[j] = NULL;
	return (ret);
}

void				ft_print_tree(t_lexit *lexdat)
{
	int			i;

	i = 1;
	if (lexdat)
	{
		if (lexdat->left)
			ft_print_tree(lexdat->left);
		ft_putstr("CURRENT INPUT : ");
		ft_putstr(lexdat->input);
		ft_putchar('\n');
		if (lexdat->redirs)
		{
			ft_putstr("CURRENT REDIR : ");
			ft_putstr(lexdat->redirs->right_target);
			ft_putchar('\n');
		}
		if (lexdat->right)
			ft_print_tree(lexdat->right);
	}
}

int				get_more_prio(char *str)
{
	if ((ft_isstrprint(str)) && (!ft_strcmp(str, ">") ||
	(str[0] == '>' && str[1] == '&') ||
	(str[1] == '>' && str[2] == '&')))
		return (REDIR_R);
	else if (!ft_strcmp(str, ">>"))
		return (REDIR_RR);
	else if (!ft_strcmp(str, "<"))
		return (REDIR_L);
	else if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	else if (ft_isstrprint(str))
		return (ARG);
	else
		return (-1);
}

int				get_prio(char *str, char **command, char **apaths)
{
	char			*path;

	if (!str)
		return (ERROR);
	if (!ft_strcmp(str, ";"))
		return (SEMICOLON);
	else if (!ft_strcmp(str, "&&") || !ft_strcmp(str, "||"))
		return (AND_OR);
	else if (!ft_strcmp(str, "|"))
		return (PIPE);
	else if ((path = find_cmd(apaths, str)) || !ft_strcmp(str, "cd") ||
	!ft_strcmp(str, "env") || !ft_strcmp(str, "echo") || !ft_strcmp(str, "exit")
	||  !ft_strcmp(str, "setenv") || !ft_strcmp(str, "unset"))
	{
		if (path)
		{
			*command = ft_strdup(path);
			ft_strdel(&path);
		}
		else
			*command = ft_strdup(str);
		return (COMMAND);
	}
	return (get_more_prio(str));
}

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

void				parsing_exing(t_sh *sh)
{
	if (double_check(sh->list))
	{
		assign_redir(sh->list, sh);
		trim_redir(sh->list);
		sh->execs = ft_tree_it(sh->list, NULL, 0);
		if (sh->execs && sh->execs->args)
			execute(sh);
		free_list(sh->list);
		sh->list = NULL;
		if (sh->hd_state)
			ft_strdel(&sh->hd_state);
	}
}

void				p_l_x(t_sh *sh)
{
	int			i;
	int			number;

	i = 0;
	number = 0;
	if (parsing_listing(&sh->list, sh->line->line, sh->env, sh))
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

void				ft_21sh(t_sh *sh)
{
	int				ret;


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
	ft_add_history(sh->line); //add line to history
	ft_putchar('\n');
	set_term_back();
	p_l_x(sh);
	if (ft_strequ(sh->line->line, "clear"))
		tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	ft_line_reset(sh->line);
}

int				main(int ac, char **av, char **envp)
{
	t_sh			*sh;
	int				i;

	(void)ac;
	(void)av;
	i = 0;
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
