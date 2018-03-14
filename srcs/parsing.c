#include "../includes/sh.h"

void				func(t_lexit *tmp, t_env *env, t_parsing *data, int node)
{
	if (node == 1)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add_node(data->to_node1, env);
		ft_strdel(&data->to_node1);
		tmp->next->prev = tmp;
	}
	if (node == 2)
	{
		if (tmp)
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = add_node(data->to_node_op, env);
			tmp->next->prev = tmp;
			data->index += 1;
		}
	}
	if (node == 3)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add_node(data->to_node2, env);
		tmp->next->prev = tmp;
	}
}

int				parsing_error(t_parsing *data, char *input, int code)
{
	char			*tmp;

	tmp = NULL;
	if (code == 1)
	{
		if (((data->ptr2 = ft_strchr(OPERATOR, input[data->index]))) &&
		data->ptr2[0] != '\0')
		{
			ft_strdel(&data->to_node1);
			data->to_node1 = NULL;
			ft_errors(1, data->ptr2, NULL);
			return (0);
		}
	}
	if (code == 2)
	{
		if (!data->breaker)
			return (0);
		if (((!ft_isstrprint(data->to_node2 =
		ft_strtrim(tmp = ft_strsub(input, data->index, data->subber)))) &&
		(data->ptr[0] != ';')) || (ft_strchr(OPERATOR, data->to_node2[0]) &&
		data->ptr[0] != ';'))
		{
			ft_strdel(&tmp);
			ft_strdel(&data->to_node2);
			data->to_node2 = NULL;
			ft_errors(1, data->ptr, NULL);
			return (0);
		}
		ft_strdel(&tmp);
		ft_strdel(&data->to_node2);
		data->to_node2 = NULL;
	}
	return (1);
}

void				index_juggle(t_parsing *data, char *input)
{
	data->latest = data->index;
	data->anex = data->index;
	while ((!ft_strchr(OPERATOR, input[data->anex])) && input[data->anex])
		data->anex++;
	data->subber = data->anex - data->latest;
}

t_lexit 			*init_node(t_lexit *tmp, t_lexit **list, t_env *env, t_parsing *data)
{
	if (!tmp)
	{
		*list = add_node(data->to_node1, env);
		ft_strdel(&data->to_node1);
		tmp = *list;
	}
	else
		func(tmp, env, data, 1);
	return (tmp);
}

void				parsing_listing(t_lexit **list, char *input, t_env *env)
{
	t_parsing	*data;
	t_lexit		*tmp;

	tmp = *list;
	data = init_data();
	if (quote_checker(data, input))
	{
		while (input[++data->index] && data->breaker)
		{
			if ((data->ptr = ft_strchr(OPERATOR, input[data->index])))
			{
				data->breaker = check_first_node(data, input);
				get_full_op(data, input);
				tmp = init_node(tmp, list, env, data);
				func(tmp, env, data, 2);
				while (ft_isspace(input[data->index]))
					data->index++;
				if (data->checker)
					data->breaker = parsing_error(data, input, 1);
				index_juggle(data, input);
				data->breaker = parsing_error(data, input, 2);
				data->checker = 0;
			}
			if (input[data->index + 1] == '\0' && data->to_node2)
			{
				func(tmp, env, data, 3);
				ft_strdel(&data->to_node2);
			}
		}
	}
	ft_memdel((void **)&data);
}
