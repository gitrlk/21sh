/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:11:43 by rfabre            #+#    #+#             */
/*   Updated: 2018/05/02 23:29:42 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		link_last_node(char *i, t_lexit **l, t_parsing *data, t_sh *sh)
{
	char	*content;
	t_lexit	*tmp;

	tmp = *l;
	content = ft_strsub(i, (data->index + 1), (data->subber - data->index));
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = add_node(content, sh);
	ft_strdel(&content);
	tmp->next->prev = tmp;
}

void		link_non_op(t_parsing *d, t_lexit **tmp, t_lexit **l, t_sh *sh)
{
	if (!(*tmp))
	{
		*l = add_node(d->content, sh);
		if (d->content)
			ft_strdel(&d->content);
		*tmp = *l;
	}
	else
	{
		while ((*tmp)->next)
			(*tmp) = (*tmp)->next;
		(*tmp)->next = add_node(d->content, sh);
		if (d->content)
			ft_strdel(&d->content);
		(*tmp)->next->prev = (*tmp);
	}
}

void		link_nodes(char *input, t_lexit **list, t_parsing *data, t_sh *sh)
{
	t_lexit	*tmp;

	tmp = *list;
	data->index--;
	data->content = ft_strsub(input, data->anex, data->check);
	data->anex = data->index + 1;
	link_non_op(data, &tmp, list, sh);
	if (ft_strchr(OPERATOR, data->to_node_op[0]) ||
		((data->to_node_op[1] == '>')
				&& data->to_node_op[2] == '&'))
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add_node(data->to_node_op, sh);
		tmp->next->prev = tmp;
		data->to_node_op[0] = '\0';
		data->to_node_op[1] = '\0';
		data->to_node_op[2] = '\0';
	}
	if (input[data->subber] == '\0' && data->wordsize)
		link_last_node(input, list, data, sh);
	data->index++;
}

int			node_lro(char *input, t_lexit **list, t_parsing *data, t_sh *sh)
{
	if (!check_left_right(input, data))
		return (0);
	link_nodes(input, list, data, sh);
	return (1);
}

int			its_over(t_insert *vals, t_parsing *data, char *input)
{
	if (input[data->index + 1] == '\0')
		return (1);
	else
		vals->i = data->index + 1;
	data->subber = data->index;
	while (data->subber < data->len)
	{
		data->subber++;
		data->last++;
	}
	vals->tmp2 = ft_strsub(input, vals->i, data->last);
	if (!ft_isstrprint(vals->tmp = ft_strtrim(vals->tmp2)))
	{
		ft_strdel(&vals->tmp);
		ft_strdel(&vals->tmp2);
		data->last = 0;
		return (1);
	}
	return (0);
}
