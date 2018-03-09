/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:14:55 by jecarol           #+#    #+#             */
/*   Updated: 2018/03/09 18:44:23 by jecarol          ###   ########.fr       */
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
	int i;

	i = 1;
	if (lexdat)
	{
		if (lexdat->left)
		{
			ft_putstr("GOING LEFT\n");
			ft_print_tree(lexdat->left);
		}
		ft_putstr(lexdat->input);
		ft_putchar('\n');
		if (lexdat->right)
		{
			ft_putstr("GOING RIGHT\n");
			ft_print_tree(lexdat->right);
		}
	}
}

int				get_prio(char *str, t_env *env)
{
	char **apaths;
	char *path;

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

t_lexit				*add_node(char *input, t_env *env)
{
	t_lexit *tmp;

	if (!(tmp = ft_memalloc(sizeof(t_lexit))))
		return (NULL);
	tmp->next = NULL;
	tmp->left = 0;
	tmp->right = 0;
	tmp->input = ft_strdup(input);
	tmp->prio = get_prio(input, env);
	return (tmp);
}

void					create_list(t_lexit **list, char **input, t_env *env)
{
	int i;
	t_lexit *tmp;

	i = 0;
	tmp = *list;
	while (input[i])
	{
		if (!tmp)
		{
			*list = add_node(input[i], env);
			tmp = *list;
		}
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = add_node(input[i], env);
			tmp->next->prev = tmp;
		}
		i++;
	}
}

int					main(int ac, char **av, char **envp)
{
	t_edit			*line;
	t_lexit			*lexdat;
	t_env				*env;
	t_norm			*values;
	t_lexit			*list;
	char				**apaths;
	int				prio;

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
		if (ft_errors(ft_pre_parser(line), NULL, NULL))
		{
			ft_putchar('\n');
			create_list(&list, line->line_split, env);
			// parse_list(list);
			lexdat = ft_tree_it(list, NULL, prio);
			apaths = ft_set_paths(env);
			ft_print_tree(lexdat);
			// if (lexdat)
			// if (ft_errors(ft_parser(lexdat), NULL, NULL))
			// {
				// ft_putchar('\n');
				// ft_final_parsing(lexdat);
				// ft_execs(lexdat, env, line);
				// ft_print_lexdat(lexdat);
			// }
		}
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
