/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:01:19 by jecarol           #+#    #+#             */
/*   Updated: 2018/05/03 01:47:40 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			kick_semi(t_lexit *list)
{
	t_lexit		*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp->prio == SEMICOLON && !tmp->next && tmp->prev)
		{
			if (tmp->input)
				ft_strdel(&tmp->input);
			if (tmp->args[0])
				ft_freetab(tmp->args);
			tmp->prev->next = NULL;
			free(tmp);
			tmp = NULL;
		}
		else
			tmp = tmp->next;
	}
}

int				parsing_error(t_parsing **data)
{
	ft_errors(1, &(*data)->ptr[0], NULL);
	free(*data);
	return (0);
}

int				ignore_first_semi(t_sh *sh)
{
	char		*tmp;
	int			i;
	int			start_go[2];

	tmp = ft_strdup(sh->line->line);
	start_go[0] = 0;
	start_go[1] = 0;
	i = 0;
	while (sh->line->line[i] && ft_isspace(sh->line->line[i]))
		i++;
	if (sh->line->line[i] == ';')
	{
		start_go[0] = i + 1;
		if (!look_for_op(sh, (i + 1)))
			return (ft_errors(1, ";", NULL));
		while (sh->line->line[i])
		{
			i++;
			start_go[1]++;
		}
		ft_strdel(&sh->line->line);
		sh->line->line = ft_strsub(tmp, start_go[0], start_go[1]);
	}
	ft_strdel(&tmp);
	return (1);
}

int				setup_parsing(t_parsing *data, t_env *env, t_sh *sh)
{
	data->env = env;
	data->empty_input = ft_strtrim(sh->line->line);
	if (data->empty_input[0] == '\0')
		data->empty = 1;
	ft_strdel(&data->empty_input);
	if (ignore_first_semi(sh))
	{
		data->len = ft_strlen(sh->line->line);
		return (1);
	}
	return (0);
}

void			ignore_quotes(char *s, t_parsing *data, int mod)
{
	if (mod == 1)
	{
		if (s[data->index] == '\'')
		{
			data->index++;
			while (s[data->index] != '\'')
				data->index++;
		}
		if (s[data->index] == '\"')
		{
			data->index++;
			while (s[data->index] != '\"')
				data->index++;
		}
	}
	if (mod == 2)
		ignore_quotes_more(s, data);
}
