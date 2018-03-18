/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:14:55 by jecarol           #+#    #+#             */
/*   Updated: 2018/03/18 23:27:46 by jecarol          ###   ########.fr       */
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
	// copies = ft_memalloc(sizeof(t_fday));
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
	else if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>") ||
	!ft_strcmp(str, "<") || !ft_strcmp(str, "<<"))
		return (REDIR);
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

void				execute_binary(t_lexit *list, t_env *env, t_fday *fd)
{
	char			**newenv;
	pid_t			pid;

	newenv = ft_fill_envp(env);
	pid = fork();
	// dup2(fd->in, 0);
	// close(fd->out);
	if (pid == 0)
	{
		dup2(fd->saved_file, 1);
		close(fd->saved_file);
		execve(list->command, list->args, newenv);
	}
	else if (pid > 0)
	{
		// close(fd->in);
		// dup2(fd->saved_in, fd->in);
		// close(fd->out);
		// dup2(fd->saved_out, fd->out);
		waitpid(pid, NULL, 0);
	}
	// close(fd->in);
	// dup2(fd->saved_out, fd->out);
	ft_freetab(newenv);
}

void  			handle_redir(char *redirection, t_sh *sh, t_lexit *lexdat)
{
		if (ft_strequ(redirection, ">"))
		{
			if ((sh->fd.saved_file = open(lexdat->right->input, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
				ft_putstr("OPEN ERROR");
			// dup2(sh->fd.in, 0);
			// close(sh->fd.out);
			// ft_putnbr(sh->fd.saved_file);
			// if ((dup2(sh->fd.saved_file, sh->fd.saved_out)) == -1)
			// 	ft_putstr("ERROR DUP");
			// ft_putstr("saved fd in : ");
			// ft_putnbr(sh->fd.saved_in);
			// ft_putchar('\n');
			// ft_putstr("saved fd out : ");
			// ft_putnbr(sh->fd.saved_out);
			// ft_putchar('\n');
			// ft_putstr("saved fd er : ");
			// ft_putnbr(sh->fd.saved_err);
			// ft_putchar('\n');
			// close(sh->fd.saved_file);
		}
    	else
      	exit(0);
}


void				execs(t_lexit *list, t_env *env, t_sh *sh)
{
	static int	redir = 0;

	if (list)
	{
		if (list->prio == REDIR)
		{
			redir = 1;
			handle_redir(list->input, sh, list);
			// close(sh->fd.saved_out);
		}
		if (list->left)
			execs(list->left, env, sh);
		if (list->prio == COMMAND)
		{
			execute_binary(list, env, &sh->fd);
			// if (redir == 1)
			// {
				// close(sh->fd.in);
				// close(sh->fd.out);
				// sh->fd.in = dup(sh->fd.saved_in);
				// sh->fd.in = dup(sh->fd.saved_out);
			// }
			// ft_putstr("saved fd in : ");
			// ft_putnbr(sh->fd.saved_in);
			// ft_putchar('\n');
			// ft_putstr("saved fd out : ");
			// ft_putnbr(sh->fd.saved_out);
			// ft_putchar('\n');
			// ft_putstr("saved fd er : ");
			// ft_putnbr(sh->fd.saved_err);
			// ft_putchar('\n');
			// if (redir)
			// {
			// 	// ft_putstr("saved file fd : ");
			// 	// ft_putnbr(sh->fd.saved_file);
			// 	// ft_putchar('\n');
			// 	// dup2(sh->fd.saved_out, fd);
			// 	// close(sh->fd.saved_file);
			// 	// close(STDOUT_FILENO);
			// 	dup2(sh->fd.saved_out, sh->fd.saved_file);
			// 	// dup2(sh->fd.saved_out, STDOUT_FILENO);
			// 	// close(sh->fd.saved_out);
			// 	// if()
			// 	// ft_putnbr(sh->fd.saved_out);
			// 	// dup2(sh->fd.)
			// 	// dup2(STDIN_FILENO, sh->fd.saved_in);
			// 	// dup2(STDOUT_FILENO, sh->fd.saved_out);
			// 	// if (sh->fd.saved_out == -1)
			// 	// {
			// 	// 	close(STDOUT_FILENO);
			// 	// 	sh->fd.saved_out = 1;
			// 	// }
			// 	// else if (sh->fd.saved_out != 1)
			// 	// 	dup2(sh->fd.saved_out, STDOUT_FILENO);
				redir = 0;
			// }
		}
		if (list->right)
			execs(list->right, env, sh);
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
		ft_strdel(&lexdat->input);
		ft_strdel(&lexdat->command);
	}
}

void				free_list(t_lexit *list)
{
	t_lexit		*tmp;

	tmp = list;
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
		if (tmp)
			free(tmp);
	}
}

void				do_magic(t_sh *sh)
{
	if (sh->line->line[0])
	{
		parsing_listing(&sh->list, sh->line->line, sh->env);
		sh->lexdat = ft_tree_it(sh->list, NULL, 0);
		execs(sh->lexdat	, sh->env, sh);
	}
	if (sh->lexdat)
		free_tree(sh->lexdat);
	if (sh->list)
	{
		free_list(sh->list);
		sh->list = NULL;
	}
}

void				do_work(t_sh *sh, t_norm *values)
{
	ft_prompt();
	while ((values->ret = read(0, &values->buf, sizeof(int))) &&
	values->buf != '\n')
	{
		handle_key(values->buf, sh->line);
		values->buf = 0;
	}
	ft_putchar('\n');
	do_magic(sh);
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
		do_work(sh, values);
	return (0);
}
