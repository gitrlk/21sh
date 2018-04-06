#include "../includes/sh.h"

// void				choose_node(t_lexit *tmp, t_env *env, t_parsing *data, int node)
// {
// 	if (node == 1)
// 	{
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = add_node(data->to_node1, env);
// 		ft_strdel(&data->to_node1);
// 		tmp->next->prev = tmp;
// 	}
// 	if (node == 2)
// 	{
// 		if (tmp)
// 		{
// 			while (tmp->next)
// 				tmp = tmp->next;
// 			tmp->next = add_node(data->to_node_op, env);
// 			tmp->next->prev = tmp;
// 			data->index += 1;
// 		}
// 	}
// 	if (node == 3)
// 	{
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = add_node(data->to_node2, env);
// 		tmp->next->prev = tmp;
// 	}
// }
//
// int				parsing_error(t_parsing *data, char *input, int code)
// {
// 	char			*tmp;
//
// 	tmp = NULL;
// 	if (code == 1)
// 	{
// 		if (((data->ptr2 = ft_strchr(OPERATOR, input[data->index]))) &&
// 		data->ptr2[0] != '\0')
// 		{
// 			ft_strdel(&data->to_node1);
// 			data->to_node1 = NULL;
// 			ft_errors(1, data->ptr2, NULL);
// 			return (0);
// 		}
// 	}
// 	if (code == 2)
// 	{
// 		if (!data->breaker)
// 			return (0);
// 		if (((!ft_isstrprint(data->to_node2 =
// 		ft_strtrim(tmp = ft_strsub(input, data->index, data->subber)))) &&
// 		(data->ptr[0] != ';')) || (ft_strchr(OPERATOR, data->to_node2[0]) &&
// 		data->ptr[0] != ';'))
// 		{
// 			ft_strdel(&tmp);
// 			ft_errors(1, data->ptr, NULL);
// 			return (0);
// 		}
// 		data->checker = 0;
// 		ft_strdel(&tmp);
// 	}
// 	return (1);
// }
//
// void				index_juggle(t_parsing *data, char *input)
// {
// 	data->latest = data->index;
// 	data->anex = data->index;
// 	while ((!ft_strchr(OPERATOR, input[data->anex])) && input[data->anex])
// 		data->anex++;
// 	data->subber = data->anex - data->latest;
// }
//
// t_lexit 			*init_node(t_lexit *tmp, t_lexit **list,
// 					t_env *env, t_parsing *data)
// {
// 	if (!tmp)
// 	{
// 		*list = add_node(data->to_node1, env);
// 		ft_strdel(&data->to_node1);
// 		tmp = *list;
// 	}
// 	else
// 		choose_node(tmp, env, data, 1);
// 	return (tmp);
// }

t_lexit			*single_node(t_lexit *tmp, t_lexit **list, t_env *env, char *input)
{
	*list = add_node(input, env);
	tmp = *list;
	return (tmp);
}

// int				end_line_checker(t_parsing *data, char *input)
// {
// 	if (input[data->index + (ft_strlen(data->to_node2))] != '\0')
// 		return(1);
// 	return (0);
// }








int				check_left_right(char *input, t_parsing *data)
{
	char			*tmp;

	if (input[data->index + 1] == '\0')
		return (0);
	if (data->index == 1)
		return (0);
	if (!ft_isstrprint(tmp = ft_strtrim(ft_strsub(input, data->anex, data->index))))
	{
		ft_strdel(&tmp);
		return (0);
	}
	ft_strdel(&tmp);
	data->subber = data->index;
	while (input[data->subber])
		data->subber++;
	while (data->index < data->subber && (!ft_strchr(OPERATOR, input[data->index])))
		data->index++;
	if (!ft_isstrprint(tmp = ft_strtrim(ft_strsub(input, data->index, data->subber))))
	{
		ft_strdel(&tmp);
		return (0);
	}
	ft_strdel(&tmp);
	return (1);
}

int				node_lro(char *input, t_lexit **list, t_parsing *data, t_lexit *tmp)
{
	(void)list;
	(void)tmp;
	if (!check_left_right(input, data))
		return (0);
	return (1);
}

int				check_if_over(char *input, t_lexit *tmp)
{

}

int				parsing_listing(t_lexit **list, char *input, t_env *env)
{
	t_parsing	*data;
	t_lexit		*tmp;
	// int			ok;

	tmp = *list;
	data = init_data();
	if (ft_strtrim(input)[0] == '\0')
		data->empty = 1;
	if (quote_checker(data, input) && !data->empty)
	{
		while (input[++data->index])
		{
			if ((data->ptr = ft_strchr(OPERATOR, input[data->index])))
			{
				if (data->ptr[0] != ';')
					 if(!node_lro(input, list, data, tmp))
						return (0);
				if (data->ptr[0] == ';')
				{
					if (check_if_over(input, tmp))
						last_node();
					else
						node_lro();
				}
			}
		}
		// 	{
		// 		data->breaker = check_first_node(data, input);
		// 		get_full_op(data, input);
		// 		tmp = init_node(tmp, list, env, data);
		// 		choose_node(tmp, env, data, 2);
		// 		while (ft_isspace(input[data->index]))
		// 			data->index++;
		// 		if (data->checker)
		// 			data->breaker = parsing_error(data, input, 1);
		// 		index_juggle(data, input);
		// 		data->breaker = parsing_error(data, input, 2);
		// 		if (!data->breaker)
		// 			break ;
		// 		if (end_line_checker(data, input) && data->breaker != 0)
		// 			if (data->to_node2 && data->to_node2[0])
		// 				ft_strdel(&data->to_node2);
		// 	}
		// 	if (input[data->index + 1] == '\0' && data->to_node2 && data->breaker)
		// 	{
 		// 		choose_node(tmp, env, data, 3);
		// 		ft_strdel(&data->to_node2);
		// 	}
		// }
		if (input && !*(list))
			tmp = single_node(tmp, list, env, input);
	}
	// if (data->breaker)
	// 	ft_strdel(&data->to_node2);
	// ok = data->breaker;
	// ft_memdel((void **)&data);
	// if (ok)
		return (1);
	// return (0);
}

// int				parsing_listing(t_lexit **list, char *input, t_env *env)
// {
// 	t_parsing	*data;
// 	t_lexit		*tmp;
// 	char			*empty_string;
// 	int			ok;
//
// 	tmp = *list;
// 	empty_string = ft_strtrim(input);
// 	data = init_data();
// 	if (empty_string[0] == '\0')
// 		data->empty = 1;
// 	ft_strdel(&empty_string);
// 	if (quote_checker(data, input) && !data->empty)
// 	{
// 		while (input[++data->index] && data->breaker)
// 		{
// 			if ((data->ptr = ft_strchr(OPERATOR, input[data->index])))
// 			{
// 				data->breaker = check_first_node(data, input);
// 				get_full_op(data, input);
// 				tmp = init_node(tmp, list, env, data);
// 				choose_node(tmp, env, data, 2);
// 				while (ft_isspace(input[data->index]))
// 					data->index++;
// 				if (data->checker)
// 					data->breaker = parsing_error(data, input, 1);
// 				index_juggle(data, input);
// 				data->breaker = parsing_error(data, input, 2);
// 				if (!data->breaker)
// 					break ;
// 				if (end_line_checker(data, input) && data->breaker != 0)
// 					if (data->to_node2 && data->to_node2[0])
// 						ft_strdel(&data->to_node2);
// 			}
// 			if (input[data->index + 1] == '\0' && data->to_node2 && data->breaker)
// 			{
//  				choose_node(tmp, env, data, 3);
// 				ft_strdel(&data->to_node2);
// 			}
// 		}
// 		if (input && !*(list))
// 			tmp = single_node(tmp, list, env, input);
// 	}
// 	if (data->breaker)
// 		ft_strdel(&data->to_node2);
// 	ok = data->breaker;
// 	ft_memdel((void **)&data);
// 	if (ok)
// 		return (1);
// 	return (0);
// }
