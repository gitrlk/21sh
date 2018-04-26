#include "../includes/sh.h"

t_lexit			*single_node(t_lexit *tmp, t_lexit **list, t_sh *sh, char *input)
{
	*list = add_node(input, sh);
	tmp = *list;
	return (tmp);
}

int 			check_left(char *tmp, char *tmp1, t_parsing *data, char *input)
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
	while (input[data->subber] && (!ft_strchr(OPERATOR, input[data->subber])))
		data->subber++;
	tmp1 = ft_strsub(input, data->index, (data->subber - data->index));
	if ((!ft_isstrprint(tmp = ft_strtrim(tmp1)) && data->to_node_op[0] != ';')
	|| tmp[0] == '\'' || tmp[0] == '\"')
	{
		ft_strdel(&tmp);
		ft_strdel(&tmp1);
		return (0);
	}
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

int					check_left_right(char *input, t_parsing *data)
{
	char			*tmp;
	char			*tmp1;

	tmp1 = NULL;
	tmp = NULL;
	if (check_left(tmp, tmp1, data, input))
		if (check_right(tmp, tmp1, data, input))
			return (1);
	return (0);
}

void				link_last_node(char *input, t_lexit **list, t_parsing *data, t_sh *sh)
{
	char 			*content;
	t_lexit			*tmp;

	tmp = *list;
	content = ft_strsub(input, (data->index + 1), (data->subber - data->index));
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = add_node(content, sh);
	ft_strdel(&content);
	tmp->next->prev = tmp;
}

void				link_non_op(t_parsing *data, t_lexit **tmp, t_lexit **list, t_sh *sh)
{
	if (!(*tmp))
	{
		*list = add_node(data->content, sh);
		if (data->content)
			ft_strdel(&data->content);
		*tmp = *list;
	}
	else
	{
		while ((*tmp)->next)
			(*tmp) = (*tmp)->next;
		(*tmp)->next = add_node(data->content, sh);
		if (data->content)
			ft_strdel(&data->content);
		(*tmp)->next->prev = (*tmp);
	}
}

void				link_nodes(char *input, t_lexit **list, t_parsing *data, t_sh *sh)
{
	t_lexit			*tmp;

	tmp = *list;
	data->index--;
	data->content = ft_strsub(input, data->anex, data->check);
	data->anex = data->index + 1;
	link_non_op(data, &tmp, list, sh);
	if (ft_strchr(OPERATOR, data->to_node_op[0]) || ((data->to_node_op[1] == '>')
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

int				node_lro(char *input, t_lexit **list, t_parsing *data, t_sh *sh)
{
	if (!check_left_right(input, data))
		return (0);
	link_nodes(input, list, data, sh);
	return (1);
}

int 		its_over(t_insert *vals, t_parsing *data, char *input)
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

void			link_last_non_op(t_parsing *data, t_sh *sh, t_lexit **tmp, t_lexit **list)
{
	if (!(*tmp))
	{
		*list = add_node(data->content, sh);
		ft_strdel(&data->tmpn);
		ft_strdel(&data->content);
		(*tmp) = *list;
	}
	else
	{
		while ((*tmp)->next)
			(*tmp) = (*tmp)->next;
		(*tmp)->next = add_node(data->content, sh);
		ft_strdel(&data->content);
		ft_strdel(&data->tmpn);
		(*tmp)->next->prev = (*tmp);
	}
}

void			last_node(t_lexit **list, char *input, t_parsing *data, t_sh *sh)
{
	int			i;
	int			j;
	t_lexit		*tmp;

	tmp = *list;
	data->content = NULL;;
	i = data->index - 1;
	j = 0;
	while (i > 0)
	{
		if (ft_strchr(OPERATOR, input[i - 1]))
			break ;
		i--;
		j++;
	}
	data->tmpn = ft_strsub(input, i, j);
	if (!sh->line->quote_complete)
		data->content = ft_strtrim(data->tmpn);
	link_last_non_op(data, sh, &tmp, list);
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
		 	if(!node_lro(input, list, data, sh))
				return(-1);
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

void 			setup_parsing(t_parsing *data, t_env *env, char *input)
{
	data->env = env;
	data->empty_input = ft_strtrim(input);
	if (data->empty_input[0] == '\0')
		data->empty = 1;
	ft_strdel(&data->empty_input);
	data->len = ft_strlen(input);
}


int				parsing_listing(t_lexit **list, char *input, t_env *env, t_sh *sh)
{
	t_parsing	*data;
	t_lexit		*tmp;

	tmp = *list;
	data = init_data();
	setup_parsing(data, env, input);
	if (quote_checker(input, sh) && !data->empty)
	{
		while (((data->index + 1) <= data->len) && input[++data->index])
		{
			if ((test_l_r(data, input, list, sh) == -1))
			{
				ft_errors(1, &data->ptr[0], NULL);
				free(data);
				return (0);
			}
		}
		if (input && !*(list))
			tmp = single_node(tmp, list, sh, input);
	}
	ft_memdel((void **)&data);
	return (1);
}
