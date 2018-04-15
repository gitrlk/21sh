/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:14:55 by jecarol           #+#    #+#             */
/*   Updated: 2018/04/15 02:22:39 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

char			**copypasta(char **src, int i)
{
	int			size;
	int			j;
	char		**ret;

	size = 0;
	j = 0;
	while (src[size])
		size++;
	if (!(ret = (char **)malloc(sizeof(char *) * size)))
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

void init_line_edit(t_edit *line)
{
	ioctl(STDERR_FILENO, TIOCGWINSZ, &line->sz);
	line->select_mode = 0;
	line->start_select = 0;
	line->end_select = 0;
	line->is_highlight = ft_strnew(0);
}

void					init_structs(t_edit *line, t_norm *values, t_fday *fd)
{
	line->hstr = NULL;
	ft_line_reset(line);
	init_line_edit(line);
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
		ft_putstr("CURRENT INPUT : ");
		ft_putstr(lexdat->input);
		ft_putchar('\n');
		if (lexdat->left)
			ft_print_tree(lexdat->left);
		// ft_putstr("CURRENT INPUT : ");
		// ft_putstr(lexdat->input);
		// ft_putchar('\n');
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
	tmp->redirs = NULL;
	tmp->checker = 0;
	tmp->command = NULL;
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
	data->env = NULL;
	data->index = -1;
	data->anex = 0;
	data->len = 0;
	data->last = 0;
	data->simpleq = 0;
	data->doubleq = 0;
	data->checker = 0;
	data->latest = 0;
	data->subber = 0;
	data->breaker = 1;
	data->empty = 0;
	data->to_node = NULL;
	data->to_node2 = NULL;
	return (data);
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

int				switch_right(t_lexit *list, t_sh *sh, int *mod)
{
	if (list->redirs && (list->redirs->redir_right == 2))
	{
		if ((sh->fd.saved_file = open(list->redirs->right_target, O_WRONLY |
		O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
			return (-1);
		else
			switch_in_out(sh, 1);
		*mod = 1;
	}
	if (list->redirs && (list->redirs->redir_right == 1))
	{
		if ((sh->fd.saved_file = open(list->redirs->right_target, O_WRONLY |
		O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
			return (-1);
		else
			switch_in_out(sh, 1);
		*mod = 1;
	}
	return (0);
}

int				switch_left(t_lexit *list, t_sh *sh, int *mod)
{
	if (list->redirs && (list->redirs->redir_left == 1))
	{
		if ((sh->fd.saved_file = open(list->redirs->left_target, O_RDONLY)) == -1)
			return (-1);
		else
			switch_in_out(sh, 2);
		*mod = *mod == 0 ? 2 : 3;
	}
	if (list->redirs && (list->redirs->redir_left == 2))
	{
		if ((sh->fd.saved_file = open("/tmp/heredoc_fd", O_RDONLY)) == -1)
			return (-1);
		else
			switch_in_out(sh, 2);
		*mod = *mod == 0 ? 2 : 3;
	}
	return (0);
}

int				switch_fd(t_lexit *list, t_sh *sh, int *mod)
{
	if ((switch_right(list, sh, mod) == -1))
		ft_errors(5, NULL, list->redirs->right_target);
	if ((switch_left(list, sh, mod) == -1))
		ft_errors(5, NULL, list->redirs->left_target);
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

void				do_pipes(t_lexit *list, t_env *env, t_sh *sh, int buf)
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
		execs_deep(list->left, env, sh, buf);
	}
	else
	{
		dup2(pipefd[0], sh->fd.saved_in);
		close(pipefd[1]);
		execs_deep(list->right, env, sh, buf);
		waitpid(pipid, &status, 0);
	}
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

void				execute_builtin(t_lexit *list, t_env *env, t_sh *sh, int buf)
{
	int				mod;

	mod = 0;
	mod = switch_fd(list, sh, &mod);
	if (mod != -1)
	{
		if (!ft_strcmp(list->args[0], "env"))
			ft_env(list, env, sh, buf);
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
	}
}

void				heredoc_work(char *i, t_sh *sh, int *ret, t_lexit *list, int buf)
{
	i = ft_strdup(sh->line->line);
	if (ft_strcmp(i, list->redirs->endoff) && (buf != 3))
	{
		ft_putstr_fd(i, ret[0]);
		ft_putchar_fd('\n', ret[0]);
	}
	if (buf == 3)
	{
		close(ret[0]);
		ft_strdel(&list->redirs->endoff);
		ret[0] = open("/tmp/heredoc_fd",O_RDONLY | O_WRONLY | O_TRUNC);
		close(ret[0]);
		ret[1] = 1;
		set_term_back();
	}
	else if (!ft_strcmp(i, list->redirs->endoff))
	{
		ft_strdel(&list->redirs->endoff);
		ret[1] = 1;
		set_term_back();
	}
	ft_strdel(&i);
	ft_putchar('\n');
}

void				init_valhd(t_hdc *valhd)
{
	valhd->ret_stop[0] = 0;
	valhd->hd = 0;
	valhd->ret_stop[1] = 0;
	valhd->tmp = NULL;
}

void				do_heredoc(t_lexit *list, t_sh *sh, int buf)
{
	t_hdc			valhd;

	init_valhd(&valhd);
	init_term();
	if ((valhd.ret_stop[0] = open("/tmp/heredoc_fd", O_WRONLY |
	O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
		ft_errors(5, NULL, "heredoc error: couldn't create heredoc");
	else
	{
		while (!valhd.ret_stop[1])
		{
			ft_prompt(2);
			ft_line_reset(sh->line);
			while ((valhd.hd = read(0, &buf, sizeof(int))))
			{
				handle_key(buf, sh->line, 1);
				if (buf == '\n' || buf == 3)
					break ;
				buf = 0;
			}
			heredoc_work(valhd.tmp, sh, valhd.ret_stop, list, buf);
		}
	}
}

void				execs_deep(t_lexit *list, t_env *env, t_sh *sh, int buf)
{
	if (list->prio == PIPE)
		do_pipes(list, env, sh, buf);
	if (list->left)
		execs_deep(list->left, env, sh, buf);
	if (list->prio == COMMAND)
	{
		if (check_if_builtin(list))
			execute_builtin(list, env, sh, buf);
		else
			execute_binary(list, env, sh);
	}
	if (list->right)
		execs_deep(list->right, env, sh, buf);
}

void				execs(t_lexit *list, t_env *env, t_sh *sh, int buf)
{
	if (list)
	{
		pid_t pid;
		int status;
		pid = fork();

		if (pid == 0)
			execs_deep(list, env, sh, buf);
		else
			waitpid(pid, &status, 0);
	}
}

void				exec_no_fork(t_lexit *list, t_env *env, t_sh *sh, int buf)
{
	if (list)
		execs_deep(list, env, sh, buf);
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

void				clean_list(t_lexit *tmp, int *checker)
{
	if (tmp->input)
		ft_strdel(&tmp->input);
	if (tmp->args)
		ft_freetab(tmp->args);
	if (tmp->command)
		ft_strdel(&tmp->command);
	if (tmp->checker && tmp->redirs->right_target)
	{
		ft_strdel(&tmp->redirs->right_target);
		*checker = 1;
	}
	if (tmp->checker && tmp->redirs->left_target)
	{
		ft_strdel(&tmp->redirs->left_target);
		*checker = 1;
		if (tmp->redirs->redir_left == 2)
			ft_strdel(&tmp->redirs->endoff);
	}
}

void				free_list(t_lexit *list)
{
	t_lexit		*tmp;
	int			checker;

	checker = 0;
	tmp = list;
	if (tmp)
	{
		while(list)
		{
			tmp = list;
			list = list->next;
			clean_list(tmp, &checker);
				free(tmp->redirs);
			if (tmp)
				free(tmp);
		}
	}
}

void				get_eof(t_lexit *node, t_sh *sh, int buf)
{
	node->redirs = (t_redir *)malloc(sizeof(t_redir));
	node->checker = 1;
	node->redirs->redir_right = 0;
	node->redirs->redir_left = 0;
	node->redirs->right_target = NULL;
	node->redirs->left_target = NULL;
	node->redirs->endoff = NULL;
	// node->redirs->follow_up = NULL;

	node->redirs->endoff = ft_strdup(node->next->args[0]);
	do_heredoc(node, sh, buf);
}

void				init_redirs(t_lexit *node)
{
	node->redirs = (t_redir *)malloc(sizeof(t_redir));
	node->checker = 1;
	node->redirs->redir_right = 0;
	node->redirs->redir_left = 0;
	node->redirs->right_target = NULL;
	node->redirs->left_target = NULL;
	node->redirs->endoff = NULL;
	// node->redirs->follow_up = NULL;
}

void				get_last_redir(t_lexit *node, t_sh *sh, int buf)
{
	t_lexit		*tmp;

	tmp = node;
	init_redirs(node->prev);
	while (tmp && (tmp->prio != SEMICOLON && tmp->prio != AND_OR && tmp->prio !=
	PIPE && tmp->prio != COMMAND))
	{
		if (tmp->next && ((tmp->prio == REDIR_R || tmp->prio == REDIR_RR)))
		{
			node->prev->redirs->redir_right = tmp->prio == REDIR_R ? 1 : 2;
			if (node->prev->redirs->right_target)
				ft_strdel(&node->prev->redirs->right_target);
			node->prev->redirs->right_target = ft_strdup(tmp->next->input);
		}
		if (tmp->next && ((tmp->prio == REDIR_L || tmp->prio == HEREDOC)))
		{
			node->prev->redirs->redir_left = tmp->prio == REDIR_L ? 1 : 2;
			if (tmp->prio == HEREDOC)
				get_eof(tmp, sh, buf);
			if (node->prev->redirs->left_target)
				ft_strdel(&node->prev->redirs->left_target);
			node->prev->redirs->left_target = ft_strdup(tmp->next->input);
		}
		tmp = tmp->next;
	}
}


void				get_redir(t_lexit *node, t_sh *sh, int buf)
{
	t_lexit		*tmp;

	tmp = node;
	if (tmp->next && (tmp->next->prio == REDIR_R || tmp->next->prio == REDIR_L ||
	tmp->next->prio == REDIR_RR || tmp->next->prio == HEREDOC))
		get_last_redir(tmp->next, sh, buf);
}

void				assign_redir(t_lexit *list, t_sh *sh, int buf)
{
	t_lexit 		*tmp;

	tmp = list;
	while (tmp && tmp->prio != SEMICOLON)
	{
		if (tmp->prio == COMMAND)
			get_redir(tmp, sh, buf);
		tmp = tmp->next;
	}
}

int				check_semi(t_sh *sh, t_lexit *lst)
{
	t_lexit		*tmp;
	int			i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		if (tmp->prio == SEMICOLON)
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

int			get_number(t_sh *sh)
{
	char		**tmp;
	int			i;

	i = 0;
	tmp = ft_strsplit(sh->line->line, ';');
	while (tmp[i])
		i++;
	ft_freetab(tmp);
	return (i);
}

t_lexit			*copy_segment(t_sh *sh, t_lexit *src)
{
	t_lexit		*dst;

	dst = add_node(src->input, sh->env);
	dst->redirs = src->redirs;
	return (dst);
}

int					check_pipe(t_lexit *node)
{
	if (node->prev->prio != COMMAND || node->next->prio != COMMAND)
		return (node->prev->prio != COMMAND ?
		ft_errors(6, NULL, node->prev->args[0]) :
		ft_errors(6, NULL, node->next->args[0]));
	return (1);
}

int					check_redirr(t_lexit *node, int *checker)
{
	if (*checker == 0)
	{
		if (node->prev->prio != COMMAND)
			return (ft_errors(6, NULL, node->prev->args[0]));
		else
			*checker = 1;
	}
	return (1);
}

int					check_redirl(t_lexit *node)
{
	if ((open(node->next->args[0], O_RDONLY)) == -1)
		return(ft_errors(4, NULL, node->next->args[0]));
	return (1);
}

int 				double_check(t_lexit *lst)
{
	int checker;
	t_lexit *tmp;

	checker = 0;
	tmp = lst;
	if (tmp)
	{
		while(tmp)
		{
			if (tmp->prio == PIPE)
				if (!check_pipe(tmp))
					return (0);
			if (tmp->prio == REDIR_R || tmp->prio == REDIR_RR)
				if (!check_redirr(tmp, &checker))
					break ;
			if (tmp->prio == REDIR_L)
				if (!check_redirl(tmp))
					break ;
			tmp = tmp->next;
		}
		if (!tmp)
			return (1);
	}
	return (0);
}

void				execute(t_sh *sh, int buf)
{
	if (check_if_builtin(sh->execs))
		exec_no_fork(sh->execs, sh->env, sh, buf);
	else if (sh->execs->prio != ARG)
		execs(sh->execs, sh->env, sh, buf);
	else
		ft_errors(6, NULL, sh->execs->args[0]);
}

t_execs			*init_igo(t_sh *sh)
{
	t_execs		*igo;

	igo = ft_memalloc(sizeof(t_execs));
	igo->tmp = sh->list;
	igo->start = NULL;
	igo->copy = NULL;
	igo->head = NULL;
	igo->tmp2 = NULL;
	igo->exec_number = get_number(sh);
	sh->execs = NULL;
	return (igo);
}

void				exec_segment(t_sh *sh, t_execs *igo, int buf)
{
	if (double_check(igo->head))
	{
		assign_redir(igo->head, sh, buf);
		sh->execs = ft_tree_it(igo->head, NULL, 0);
		igo->tmp2 = sh->execs;
		execute(sh, buf);
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

void				exec_last_segment(t_sh *sh, t_execs *igo, int buf)
{
	if (double_check(igo->head))
	{
		assign_redir(igo->head, sh, buf);
		sh->execs = ft_tree_it(igo->head, NULL, 0);
		execute(sh, buf);
		while (igo->copy->first != 1)
			igo->copy = igo->copy->prev;
		free_list(igo->copy);
		igo->copy = NULL;
		sh->execs = NULL;
	}
}

void				cut_list(t_sh *sh, t_execs *igo)
{
	if (!igo->copy)
	{
		igo->copy = copy_segment(sh, igo->tmp);
		igo->copy->first = 1;
		igo->head = igo->copy;
	}
	else
	{
		igo->copy->next = copy_segment(sh, igo->tmp);
		igo->copy->next->first = 0;
		igo->copy->next->prev = igo->copy;
		igo->copy = igo->copy->next;
	}
}

int				free_igo(t_execs *igo, int mod)
{
	int			exec_number;

	exec_number = igo->exec_number;
	if (mod == 1)
	{
		free(igo);
		return (1);
	}
	else
	{
		free(igo);
		return (exec_number);
	}
}

int				get_execs(t_sh *sh, int buf)
{
	t_execs		*igo;
	igo = init_igo(sh);
	if (check_semi(sh, igo->tmp))
	{
		while (igo->tmp)
		{
			cut_list(sh, igo);
			if (igo->tmp->next && igo->tmp->next->prio == SEMICOLON)
				exec_segment(sh, igo, buf);
			if (igo->tmp->prio != SEMICOLON && !igo->tmp->next)
				exec_last_segment(sh, igo, buf);
			igo->tmp = igo->tmp->next;
		}
		return (free_igo(igo, 2));
	}
	else
		return (free_igo(igo, 1));
}

void				parsing_exing(t_sh *sh, int buf)
{
	if (double_check(sh->list))
	{
		assign_redir(sh->list, sh, buf);
		sh->execs = ft_tree_it(sh->list, NULL, 0);
		if (sh->execs->args)
			execute(sh, buf);
		free_list(sh->list);
		sh->list = NULL;
	}
}

void				p_l_x(t_sh *sh, int buf)
{
	int			i;
	int			number;

	i = 0;
	number = 0;
	if (parsing_listing(&sh->list, sh->line->line, sh->env))
	{
		number = get_execs(sh, buf);
		if (number == 1)
			if (sh->list)
				parsing_exing(sh, buf);
	}
	if (sh->list)
	{
		free_list(sh->list);
		sh->list = NULL;
	}
}

void				ft_21sh(t_sh *sh, t_norm *values)
{
	ft_prompt(1);
	init_term();
	while ((values->ret = read(0, &values->buf, sizeof(int))) &&
	values->buf != '\n')
	{
		handle_key(values->buf, sh->line, 0);
		values->buf = 0;
	}
	ft_add_history(sh->line); //add line to history
	ft_putchar('\n');
	set_term_back();
	p_l_x(sh, values->buf);
	if (ft_strequ(sh->line->line, "clear"))
		tputs(tgetstr("cl", NULL), 1, ft_pointchar);
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
	listen_signal();
	while (envp[values->i])
		ft_push_env(&sh->env, envp[values->i++]);
	while (42)
		ft_21sh(sh, values);
	return (0);
}
