/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:14:55 by jecarol           #+#    #+#             */
/*   Updated: 2018/03/11 20:58:03 by jecarol          ###   ########.fr       */
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
		ft_putstr(lexdat->input);
		ft_putchar('\n');
		if (lexdat->right)
			ft_print_tree(lexdat->right);
	}
}

int				get_prio(char *str, t_env *env)
{
	char			**apaths;
	char			*path;

	apaths = ft_set_paths(env);
	if (!ft_strcmp(str, ";"))
		return (SEMICOLON);
	else if (!ft_strcmp(str, "&&") || !ft_strcmp(str, "||"))
		return (AND_OR);
	else if (!ft_strcmp(str, "|"))
		return (PIPE);
	else if ((path = find_cmd(apaths, str)))
		return (COMMAND);
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

	if (!(tmp = ft_memalloc(sizeof(t_lexit))))
		return (NULL);
	tmp->next = NULL;
	tmp->left = 0;
	tmp->right = 0;
	tmp->input = ft_strdup(input);
	tmp->prio = get_prio(input, env);
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

void				create_list(t_lexit **list, char *input, t_env *env)
{
	t_parsing	*data;
	t_lexit		*tmp;

	(void)env;

	tmp = *list;
	data = ft_memalloc(sizeof(t_parsing));
	data->index = 0;
	data->simpleq = 0;
	data->doubleq = 0;
	data->checker = 0;
	data->latest = 0;
	data->subber = 0;
	data->to_node1 = NULL;
	// data->to_node_op = NULL;
	data->to_node2 = NULL;
	if (quote_checker(data, input))
	{
		while (input[data->index])
		{
			if ((data->ptr = ft_strchr(OPERATOR, input[data->index])))
			{
				data->anex = data->latest;
				while ((!ft_strchr(OPERATOR, input[data->anex])) && input[data->anex])
					data->anex++;
				ft_putnbr(data->anex);
				data->subber = data->anex - data->latest;
				data->to_node_op[0] = data->ptr[0];
				data->checker = 1;
				if (!ft_isstrprint(ft_strtrim(data->to_node1 = (ft_strsub(input, data->latest, data->subber)))) && (data->ptr[0] != ';'))
				{
					ft_strdel(&data->to_node1);
					data->to_node1 = NULL;
					ft_errors(1, data->ptr, NULL);
					break ;
				}
				get_full_op(data, input);
				ft_putstr("THIS IS TO_NODE1 : ");
				ft_putstr(data->to_node1);
				ft_putchar('\n');
				ft_putstr("THIS IS TO_NODE_OP : ");
				ft_putstr(data->to_node_op);
				ft_putchar('\n');
				data->index += 1;
				while (ft_isspace(input[data->index]))
					data->index++;
				if (data->checker)
					if (((data->ptr2 = ft_strchr(OPERATOR, input[data->index]))) && data->ptr2[0] != '\0')
					{
						ft_strdel(&data->to_node1);
						data->to_node1 = NULL;
						ft_errors(1, data->ptr2, NULL);
						break ;
					}
				data->latest = data->index;
				data->anex = data->index;
				while ((!ft_strchr(OPERATOR, input[data->anex])) && input[data->anex])
					data->anex++;
				data->subber = data->anex - data->latest;
				if (((!ft_isstrprint(data->to_node2 = ft_strtrim(ft_strsub(input, data->index, data->subber)))) && (data->ptr[0] != ';')) || (ft_strchr(OPERATOR, data->to_node2[0]) && data->ptr[0] != ';'))
				{
					ft_strdel(&data->to_node2);
					data->to_node2 = NULL;
					ft_errors(1, data->ptr, NULL);
					break ;
				}
				else
					data->checker = 0;
			}
			if (input[data->index + 1] == '\0' && data->to_node2)
			{
				ft_putstr("THIS IS TO_NODE2 : ");
				ft_putstr(data->to_node2);
				ft_putchar('\n');
			}
			data->index++;
			// if (!tmp)
			// {
			// 	*list = add_node(input[data->index], env);
			// 	tmp = *list;
			// }
			// else
			// {
			// 	while (tmp->next)
			// 		tmp = tmp->next;
			// 	tmp->next = add_node(input[data->index], env);
			// 	tmp->next->prev = tmp;
			// }
			// if ()
			// data->index++;
		}
	}
}

int				main(int ac, char **av, char **envp)
{
	t_edit		*line;
	t_lexit		*lexdat;
	t_env			*env;
	t_norm		*values;
	t_lexit		*list;
	char			**apaths;
	int			prio;

	(void)ac;
	(void)av;
	prio = 0;
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
		values->buf != 10)
		{
			handle_key(values->buf, line);
			values->buf = 0;
		}
		// if (ft_errors(ft_pre_parser(line), NULL, NULL))
		// {
			ft_putchar('\n');
			create_list(&list, line->line, env);
			// parse_list(list);
			// lexdat = ft_tree_it(list, NULL, prio);
			apaths = ft_set_paths(env);
			// ft_print_tree(lexdat);
			// if (lexdat)
			// if (ft_errors(ft_parser(lexdat), NULL, NULL))
			// {
				// ft_putchar('\n');
				// ft_final_parsing(lexdat);
				// ft_execs(lexdat, env, line);
				// ft_print_lexdat(lexdat);
			// }
		// }
		ft_add_history(line); //add line to history
		// ft_free_lexdat(lexdat);
		// ft_free_lexdat(list);
		// lexdat = NULL;
		// list = NULL;''
		if (ft_strequ(line->line, "clear"))
			tputs(tgetstr("cl", NULL), 1, ft_pointchar);
		if (ft_strequ(line->line, "exit"))
			exit(0);
		ft_line_reset(line);
	}
	return (0);
}
