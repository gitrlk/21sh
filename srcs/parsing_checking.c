/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checking.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:11:40 by rfabre            #+#    #+#             */
/*   Updated: 2018/05/03 01:50:01 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int				check_if_over(char *input, t_parsing *data)
{
	t_insert	vals;

	vals.tmp = NULL;
	vals.tmp2 = NULL;
	vals.i = 0;
	if (its_over(&vals, data, input))
		return (1);
	if (ft_strchr(OPERATOR, vals.tmp[0]))
	{
		ft_strdel(&vals.tmp);
		ft_strdel(&vals.tmp2);
		return (-1);
	}
	ft_strdel(&vals.tmp);
	ft_strdel(&vals.tmp2);
	data->last = 0;
	return (0);
}

int				check_left(char *tmp, char *tmp1, t_parsing *data, char *input)
{
	if (input[data->index + 1] == '\0' && data->to_node_op[0] != ';')
		return (0);
	if (data->index == 1)
		return (0);
	data->check = data->to_node_op[1] == '\0' ? data->index - data->anex :
		data->index - (data->anex + 1);
	if (data->to_node_op[1] != '\0')
	{
		if (ft_isdigit(data->to_node_op[0]))
			data->check = data->to_node_op[0] == '\0' ? data->index - data->anex
				: data->index - (data->anex + 2);
	}
	tmp1 = ft_strsub(input, data->anex, data->check);
	if (!ft_isstrprint(tmp = ft_strtrim(tmp1)))
	{
		ft_strdel(&tmp1);
		ft_strdel(&tmp);
		return (0);
	}
	ft_strdel(&tmp);
	ft_strdel(&tmp1);
	data->subber = data->index;
	data->subber++;
	data->index++;
	return (1);
}

int				check_right(char *tmp, char *tmp1, t_parsing *data, char *input)
{
	if (input[data->subber])
		if (input[data->subber + 1] != '\0' &&
		ft_strchr(OPERATOR, input[data->subber]))
			data->subber++;
	while ((input[data->subber]) && !ft_strchr(OPERATOR, input[data->subber]))
	{
		ignore_quotes(input, data, 2);
		data->subber++;
	}
	tmp1 = ft_strsub(input, data->index, (data->subber - data->index));
	if ((!ft_isstrprint(tmp = ft_strtrim(tmp1)) && data->to_node_op[0] != ';')
			|| ((tmp[0] == '\'' || tmp[0] == '\"') && tmp[1] == '\0'))
		return (return_free(tmp, tmp1));
	if (ft_strchr(OPERATOR, tmp[0]) && tmp[0] != '\0')
	{
		ft_strdel(&tmp);
		ft_strdel(&tmp1);
		return (0);
	}
	if (input[data->subber] == '\0')
		data->wordsize = ft_strlen(tmp);
	ft_strdel(&tmp);
	ft_strdel(&tmp1);
	return (1);
}

int				check_left_right(char *input, t_parsing *data)
{
	char		*tmp;
	char		*tmp1;

	tmp1 = NULL;
	tmp = NULL;
	if (check_left(tmp, tmp1, data, input))
		if (check_right(tmp, tmp1, data, input))
			return (1);
	return (0);
}

int				test_l_r(t_parsing *data, char *input, t_lexit **list, t_sh *sh)
{
	int			ret_mem[2];

	ret_mem[0] = 0;
	ret_mem[1] = 0;
	if ((data->ptr = ft_strchr(OPERATOR, input[data->index])))
	{
		data->to_node_op[0] = data->ptr[0];
		get_full_op(data, input);
		if (data->ptr[0] != ';')
		{
			ret_mem[1] = data->index;
			if (!node_lro(input, list, data, sh))
				return (-1);
		}
		if (data->ptr[0] == ';')
		{
			ret_mem[1] = data->index;
			if ((ret_mem[0] = check_if_over(input, data)) != -1)
				data->index = ret_mem[1];
			else if (ret_mem[0] == -1)
				return (ret_mem[0]);
			node_lro(input, list, data, sh);
		}
	}
	return (0);
}
