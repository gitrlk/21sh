/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:50:04 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/29 18:54:43 by rlkcmptr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			add_quote_to_args(char **args, char *str)
{
	int			i;

	i = 0;
	if (!args[0])
	{
		args = (char **)malloc(sizeof(char *) * 2);
		args[0] = ft_strdup(str);
		args[1] = NULL;
	}
	else
	{
		while (args[i])
			i++;
		args[i] = ft_strdup(str);
		args[i + 1] = NULL;
	}
}

void			replace_quote(t_lexit *node, t_sh *sh)
{
	int			i;

	i = 0;
	while (node->args[i])
	{
		if ((node->args[i][0] == '\'' || node->args[i][0] == '\"') &&
		(!is_quote_closed(node->args[i], '\'') &&
		(!is_quote_closed(node->args[i], '\"'))))
		{
			ft_strdel(&node->args[i]);
			if (sh->line->q_str)
			{
				node->args[i] = ft_strdup(sh->line->q_str);
				ft_strdel(&sh->line->q_str);
			}
		}
		i++;
	}
}

t_lexit			*add_node(char *input, t_sh *sh)
{
	t_lexit		*tmp;
	char		**apaths;
	int			i;

	i = 0;
	if (!input)
		return (NULL);
	if (!(tmp = ft_memalloc(sizeof(t_lexit))))
		return (NULL);
	(void)sh;
	apaths = ft_set_paths(sh->env);
	tmp->input = ft_strtrim(input);
	tmp->args = ft_prep_input(input);
	replace_quote(tmp, sh);
	init_node(tmp);
	tmp->prio = get_prio(tmp->args[0], &tmp->command, apaths);
	ft_freetab(apaths);
	return (tmp);
}

void			get_full_grtrthn(t_parsing *data, char *input)
{
	if (input[data->index + 1] == '>')
	{
		data->to_node_op[1] = '>';
		data->index++;
	}
	else if (input[data->index + 1] == '&')
	{
		data->to_node_op[0] = input[data->index - 1];
		data->to_node_op[1] = '>';
		data->to_node_op[2] = '&';
		data->index++;
	}
}

void			get_full_op(t_parsing *data, char *input)
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
		get_full_grtrthn(data, input);
	if (data->to_node_op[0] == '<')
		if (input[data->index + 1] == '<')
		{
			data->to_node_op[1] = '<';
			data->index++;
		}
}
