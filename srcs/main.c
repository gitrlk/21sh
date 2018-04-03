/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:14:55 by jecarol           #+#    #+#             */
/*   Updated: 2018/04/03 14:42:19 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void					init_structs(t_edit *line, t_norm *values, t_fday *fd)
{
	line->hstr = NULL;
	ft_line_reset(line);
	line->sz = ft_init(line);
	values->buf = 0;
	values->i = 0;
	values->ret = 0;
	fd->saved_in = STDIN_FILENO;
	fd->saved_out = STDOUT_FILENO;
	fd->saved_err = STDERR_FILENO;
	fd->in = 0;
	fd->out = 1;
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
		if (lexdat->right)
			ft_print_tree(lexdat->right);
	}
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
	else if ((path = find_cmd(apaths, str)))
	{
		*command = ft_strdup(path);
		ft_strdel(&path);
		return (COMMAND);
	}
	else if (!ft_strcmp(str, ">"))
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

t_lexit			*add_node(char *input, t_env *env)
{
	t_lexit		*tmp;
	char			**apaths;

	apaths = ft_set_paths(env);
	if (!input)
		return (NULL);
	if (!(tmp = ft_memalloc(sizeof(t_lexit))))
		return (NULL);
	tmp->next = NULL;
	tmp->left = 0;
	tmp->right = 0;
	tmp->input = ft_strtrim(input);
	tmp->args = ft_prep_input(input);

	//
	// update env si necessaire
	//

	tmp->prio = get_prio(tmp->args[0], &tmp->command, apaths);
	ft_freetab(apaths);
	return (tmp);
}

int				quote_checker(t_parsing *data, char *input)
{
	data->quote_checker = 0;
	while (input[data->quote_checker])
	{
		if (input[data->quote_checker] == '\'')
			data->simpleq++;
		if (input[data->quote_checker] == '\"')
			data->doubleq++;
		if (input[data->quote_checker + 1] == '\0')
		{
			if (data->simpleq % 2)
				return (ft_errors(2, NULL, NULL));
			if (data->doubleq % 2)
				return (ft_errors(3, NULL, NULL));
		}
		data->quote_checker++;
	}
	return (1);
}

void				get_full_op(t_parsing *data, char *input)
{
	if (data->to_node_op[0] == '|')
			if (input[data->index + 1] == '|')
			{
				data->to_node_op[1] = '|';
				data->index++;
			}
		if (data->to_node_op[0] == '&')
				if (input[data->index + 1] == '&')
				{
					data->to_node_op[1] = '&';
					data->index++;
				}
		if (data->to_node_op[0] == '>')
				if (input[data->index + 1] == '>')
				{
					data->to_node_op[1] = '>';
					data->index++;
				}
		if (data->to_node_op[0] == '<')
				if (input[data->index + 1] == '<')
				{
					data->to_node_op[1] = '<';
					data->index++;
				}

}

t_parsing		*init_data(void)
{
	t_parsing *data;

	data = ft_memalloc(sizeof(t_parsing));
	data->index = -1;
	data->simpleq = 0;
	data->doubleq = 0;
	data->checker = 0;
	data->latest = 0;
	data->subber = 0;
	data->breaker = 1;
	data->empty = 0;
	data->to_node1 = NULL;
	data->to_node2 = NULL;
	return (data);
}

int				check_first_node(t_parsing *data, char *input)
{
	char *tmp;

	data->anex = data->latest;
	while ((!ft_strchr(OPERATOR, input[data->anex])) && input[data->anex])
		data->anex++;
	data->subber = data->anex - data->latest;
	data->to_node_op[0] = data->ptr[0];
	if (!ft_isstrprint((tmp = ft_strtrim(data->to_node1 =
	(ft_strsub(input, data->latest, data->subber))))) && (data->ptr[0] != ';'))
	{
		ft_strdel(&data->to_node1);
		data->to_node1 = NULL;
		ft_strdel(&tmp);
		ft_errors(1, data->ptr, NULL);
		return (0);
	}
	ft_strdel(&tmp);
	data->checker = 1;
	return (1);
}

void				switch_in_out(t_sh *sh, int in_out)
{
	if (in_out == 1)
	{
		sh->fd.saved_out = dup(1);
		dup2(sh->fd.saved_file, 1);
		close(sh->fd.saved_file);
	}
	if (in_out == 2)
	{
		sh->fd.saved_in = dup(0);
		dup2(sh->fd.saved_file, 0);
		close(sh->fd.saved_file);
	}
}

int				switch_fd(t_lexit *list, t_sh *sh, int *mod)
{
	if (list->redirs && (list->redirs->redir_right == 2))
	{
		if ((sh->fd.saved_file = open(list->redirs->right_target, O_WRONLY | O_APPEND)) == -1)
		{
			ft_errors(5, NULL, list->redirs->right_target);
			return (-1);
		}
		else
			switch_in_out(sh, 1);
		*mod = 1;
	}
	if (list->redirs && (list->redirs->redir_right == 1))
	{
		if ((sh->fd.saved_file = open(list->redirs->right_target, O_WRONLY |
		O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
		{
			ft_errors(5, NULL, list->redirs->right_target);
			return (-1);
		}
		else
			switch_in_out(sh, 1);
		*mod = 1;
	}
	if (list->redirs && (list->redirs->redir_left == 1))
	{
		if ((sh->fd.saved_file = open(list->redirs->left_target, O_RDONLY)) == -1)
		{
			ft_errors(4, NULL, list->redirs->left_target);
			return (-1);
		}
		else
			switch_in_out(sh, 2);
		*mod = *mod == 0 ? 2 : 3;
	}
	return (*mod);
}

void				reset_fd(t_sh *sh, int mod)
{
	if (mod == 1)
	{
		dup2(sh->fd.saved_out, 1);
		close(sh->fd.saved_out);
	}
	if (mod == 2)
	{
		dup2(sh->fd.saved_in, 0);
		close(sh->fd.saved_in);
	}
	if (mod == 3)
	{
		dup2(sh->fd.saved_out, 1);
		close(sh->fd.saved_out);
		dup2(sh->fd.saved_in, 0);
		close(sh->fd.saved_in);
	}
}

void				execute_binary(t_lexit *list, t_env *env, t_sh *sh)
{
	char			**newenv;
	// pid_t			pid;
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

void				do_pipes(t_lexit *list, t_env *env, t_sh *sh)
{
	pid_t pipid;
	int pipefd[2];
	int status;

	pipe(pipefd);
	pipid = fork();
	if (pipid == 0)
	{
		dup2(pipefd[1], sh->fd.saved_out);
		close(pipefd[0]);
		execs_deep(list->left, env, sh);
	}
	else
	{
		dup2(pipefd[0], sh->fd.saved_in);
		close(pipefd[1]);
		waitpid(pipid, &status, 0);
		execs_deep(list->right, env, sh);
	}
}

void				execs_deep(t_lexit *list, t_env *env, t_sh *sh)
{
	if (list->prio == PIPE)
		do_pipes(list, env, sh);
	if (list->prio == COMMAND)
		execute_binary(list, env, sh);
	if (list->left)
		execs_deep(list->left, env, sh);
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

void				free_tree(t_lexit *lexdat)
{
	if (lexdat)
	{
		if (lexdat->left)
			free_tree(lexdat->left);
		if (lexdat->right)
			free_tree(lexdat->right);
		if (lexdat->input && lexdat->input[0])
			ft_strdel(&lexdat->input);
		if (lexdat->command && lexdat->command[0])
			ft_strdel(&lexdat->command);
		if (lexdat->redirs && lexdat->redirs->right_target)
			ft_strdel(&lexdat->redirs->right_target);
		if (lexdat->redirs && lexdat->redirs->left_target)
			ft_strdel(&lexdat->redirs->left_target);
	}
}

void				free_list(t_lexit *list)
{
	t_lexit		*tmp;

	tmp = list;
	if (tmp)
	{
		while(list)
		{
			tmp = list;
			list = list->next;
			if (tmp->input)
				ft_strdel(&tmp->input);
			if (tmp->args)
				ft_freetab(tmp->args);
			if (tmp->command)
				ft_strdel(&tmp->command);
			if (tmp->redirs && tmp->redirs->right_target)
				ft_strdel(&tmp->redirs->right_target);
			if (tmp->redirs && tmp->redirs->left_target)
				ft_strdel(&tmp->redirs->left_target);
			if (tmp->redirs)
				free(tmp->redirs);
			if (tmp)
				free(tmp);
		}
	}
}

void				get_last_redir(t_lexit *node)
{
	t_lexit		*tmp;

	tmp = node;
	node->prev->redirs = (t_redir *)malloc(sizeof(t_redir));
	node->prev->redirs->redir_right = 0;
	node->prev->redirs->redir_left = 0;
	node->prev->redirs->right_target = NULL;
	node->prev->redirs->left_target = NULL;
	while (tmp && (tmp->prio != SEMICOLON && tmp->prio != AND_OR && tmp->prio != PIPE && tmp->prio != COMMAND))
	{
		if (tmp->next && ((tmp->prio == REDIR_R || tmp->prio == REDIR_RR)&& tmp->next->prio == ARG))
		{
			node->prev->redirs->redir_right = tmp->prio == REDIR_R ? 1 : 2;
			if (node->prev->redirs->right_target)
				ft_strdel(&node->prev->redirs->right_target);
			node->prev->redirs->right_target = ft_strdup(tmp->next->input);
		}
		if (tmp->next && (tmp->prio == REDIR_L && tmp->next->prio == ARG))
		{
			node->prev->redirs->redir_left = 1;
			if (node->prev->redirs->left_target)
				ft_strdel(&node->prev->redirs->left_target);
			node->prev->redirs->left_target = ft_strdup(tmp->next->input);
		}
		tmp = tmp->next;
	}
}


void				get_redir(t_lexit *node)
{
	t_lexit		*tmp;

	tmp = node;
	if (tmp->next && (tmp->next->prio == REDIR_R || tmp->next->prio == REDIR_L || tmp->next->prio == REDIR_RR))
		get_last_redir(tmp->next);
}

void				assign_redir(t_lexit *list)
{
	t_lexit 		*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->prio == COMMAND)
			get_redir(tmp);
		tmp = tmp->next;
	}
}

void				parsing_lexing(t_sh *sh)
{
	if(parsing_listing(&sh->list, sh->line->line, sh->env))
	{
		assign_redir(sh->list);
		sh->lexdat = ft_tree_it(sh->list, NULL, 0);
		// ft_print_tree(sh->lexdat);
		execs(sh->lexdat, sh->env, sh);
		if (sh->lexdat)
				free_tree(sh->lexdat);
	}
	free_list(sh->list);
	sh->list = NULL;

}

void				ft_21sh(t_sh *sh, t_norm *values)
{
	ft_prompt();
	while ((values->ret = read(0, &values->buf, sizeof(int))) &&
	values->buf != '\n')
	{
		handle_key(values->buf, sh->line);
		values->buf = 0;
	}
	ft_putchar('\n');
	parsing_lexing(sh);
	ft_add_history(sh->line); //add line to history
	if (ft_strequ(sh->line->line, "clear"))
		tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	if (ft_strequ(sh->line->line, "exit"))
		exit(0);
	ft_line_reset(sh->line);
}

int				main(int ac, char **av, char **envp)
{
	t_norm		*values;
	t_sh			*sh;

	(void)ac;
	(void)av;
	sh = ft_memalloc(sizeof(t_sh));
	sh->line = ft_memalloc(sizeof(t_edit));
	values = ft_memalloc(sizeof(t_norm));
	init_structs(sh->line, values, &sh->fd);
	while (envp[values->i])
		ft_push_env(&sh->env, envp[values->i++]);
	while (42)
		ft_21sh(sh, values);
	return (0);
}
