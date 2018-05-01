/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:11:47 by rfabre            #+#    #+#             */
/*   Updated: 2018/05/01 16:22:26 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

t_lexit			*single_node(t_lexit *tmp, t_lexit **l, t_sh *sh, char *i)
{
	*l = add_node(i, sh);
	tmp = *l;
	return (tmp);
}

void			lnk_last_noop(t_parsing *d, t_sh *sh, t_lexit **t, t_lexit **l)
{
	if (!(*t))
	{
		*l = add_node(d->content, sh);
		ft_strdel(&d->tmpn);
		ft_strdel(&d->content);
		(*t) = *l;
	}
	else
	{
		while ((*t)->next)
			(*t) = (*t)->next;
		(*t)->next = add_node(d->content, sh);
		ft_strdel(&d->content);
		ft_strdel(&d->tmpn);
		(*t)->next->prev = (*t);
	}
}

void			last_node(t_lexit **list, char *s, t_parsing *data, t_sh *sh)
{
	int			i;
	int			j;
	t_lexit		*tmp;

	tmp = *list;
	data->content = NULL;
	i = data->index - 1;
	j = 0;
	while (i > 0)
	{
		if (ft_strchr(OPERATOR, s[i - 1]))
			break ;
		i--;
		j++;
	}
	data->tmpn = ft_strsub(s, i, j);
	if (!sh->line->quote_complete)
		data->content = ft_strtrim(data->tmpn);
	lnk_last_noop(data, sh, &tmp, list);
}

void			setup_parsing(t_parsing *data, t_env *env, char *input)
{
	data->env = env;
	data->empty_input = ft_strtrim(input);
	if (data->empty_input[0] == '\0')
		data->empty = 1;
	ft_strdel(&data->empty_input);
	data->len = ft_strlen(input);
}

void			ignore_quotes(char *s, t_parsing *data)
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

int				parsing_listing(t_lexit **list, char *s, t_env *env, t_sh *sh)
{
	t_parsing	*data;
	t_lexit		*tmp;

	tmp = *list;
	data = init_data();
	setup_parsing(data, env, s);
	if (quote_checker(s, sh) && !data->empty)
	{
		while (((data->index + 1) <= data->len) && s[++data->index])
		{
			ignore_quotes(s, data);
			if ((test_l_r(data, s, list, sh) == -1))
			{
				ft_errors(1, &data->ptr[0], NULL);
				free(data);
				return (0);
			}
		}
		if (s && !*(list))
			tmp = single_node(tmp, list, sh, s);
	}
	ft_memdel((void **)&data);
	return (1);
}
