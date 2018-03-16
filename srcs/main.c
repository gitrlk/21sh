/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:14:55 by jecarol           #+#    #+#             */
/*   Updated: 2018/03/16 20:49:33 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"

void					ft_setvalues(t_edit *line, t_norm *values)
{
	line->hstr = NULL;
	ft_line_reset(line);
	line->sz = ft_init(line);
	values->buf = 0;
	values->i = 0;
	values->ret = 0;
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

void				execute_binary(t_lexit *list, t_env *env)
{
	char			**newenv;
	pid_t			pid;

	newenv = ft_fill_envp(env);
	pid = fork();
	if (pid == 0)
		execve(list->command, list->args, newenv);
	else if (pid > 0)
		wait (0);
	ft_freetab(newenv);
}

void  			handle_redir(char *redirection, t_env *env, t_lexit *list, t_fday *cpy)
{
	// int			file;
	int 		dupped;

	(void)env;
	dupped = STDOUT_FILENO;
	// file = 0;
		if (ft_strequ(redirection, ">"))
		{
			if ((cpy->saved_file = open(list->right->input, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
				ft_putstr("OPEN ERROR");
			// ft_putstr("MAILLON RIGHT : ");
			// ft_putstr(list->right->input);
			// cpy->saved_in = dup(STDIN_FILENO);
			// cpy->saved_out = dup(STDOUT_FILENO);
			if ((dup2(cpy->saved_file, dupped)) == -1)
				ft_putstr("ERROR DUP");
		}
    	else
      	exit(0);
}


void				execs(t_lexit *list, t_env *env)
{
	static int	redir = 0;
	t_fday		cpy;

	if (list)
	{
		if (list->prio == REDIR)
		{
			redir = 1;
			handle_redir(list->input, env, list, &cpy);
			close(cpy.saved_file);
			// if (cpy.saved_out == -1)
			// {
			// 	close(STDOUT_FILENO);
			// 	cpy.saved_out = 1;
			// }
			// else if (cpy.saved_out != 1)
			// 	dup2(cpy.saved_out, STDOUT_FILENO);
		}
		if (list->left)
			execs(list->left, env);
		if (list->prio == COMMAND)
		{
			execute_binary(list, env);
			if (redir)
			{
				// if (cpy.saved_in != 0)
				// 	close(cpy.saved_in);
					// cpy.saved_in = 0;

					// cpy.saved_out = 1;
				// ft_putstr_fd("OUESHEU", STDOUT_FILENO);
				dup2(STDIN_FILENO, cpy.saved_in);
				dup2(STDOUT_FILENO, cpy.saved_out);
				if (cpy.saved_out == -1)
				{
					close(STDOUT_FILENO);
					cpy.saved_out = 1;
				}
				else if (cpy.saved_out != 1)
					dup2(cpy.saved_out, STDOUT_FILENO);
// ft_putstr_fd("AWEEE", STDOUT_FILENO);
				// if (cpy.saved_err == -1)
				// {
				// 	close(cpy.saved_err);
				// 	cpy.saved_err = 2;
				// }
				redir = 0;
			}
		}
		if (list->right)
			execs(list->right, env);
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

int				main(int ac, char **av, char **envp)
{
	t_edit		*line;
	t_lexit		*lexdat;
	t_env			*env;
	t_norm		*values;
	t_lexit		*list;

	(void)ac;
	(void)av;
	env = NULL;
	lexdat = NULL;
	list = NULL;
	line = ft_memalloc(sizeof(t_edit));
	values = ft_memalloc(sizeof(t_norm));
	ft_setvalues(line, values);
	while (envp[values->i])
		ft_push_env(&env, envp[values->i++]);
	while (42)
	{
		ft_prompt();
		while ((values->ret = read(0, &values->buf, sizeof(int))) &&
		values->buf != '\n')
		{
			handle_key(values->buf, line);
			values->buf = 0;
		}
		ft_putchar('\n');
		if (line->line)
		{
			parsing_listing(&list, line->line, env);
			lexdat = ft_tree_it(list, NULL, 0);
			execs(lexdat, env);
		}
		if (lexdat)
			free_tree(lexdat);
		if (list)
		{
			free_list(list);
			list = NULL;
		}
		ft_add_history(line); //add line to history
		if (ft_strequ(line->line, "clear"))
			tputs(tgetstr("cl", NULL), 1, ft_pointchar);
		if (ft_strequ(line->line, "exit"))
			exit(0);
		ft_line_reset(line);
	}
	return (0);
}
