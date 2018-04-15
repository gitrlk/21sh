#include "sh.h"
#include<stdio.h>

t_lexit			*single_node(t_lexit *tmp, t_lexit **list, t_env *env, char *input)
{
	*list = add_node(input, env);
	tmp = *list;
	return (tmp);
}

int				check_left_right(char *input, t_parsing *data)
{
	char			*tmp;
	char			*tmp1;

	tmp1 = NULL;
	if (input[data->index + 1] == '\0')
		return (0);
	if (data->index == 1)
		return (0);
	data->check = data->to_node_op[1] == '\0' ? data->index - data->anex : data->index - (data->anex + 1);
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
	if (input[data->subber + 1] != '\0' && ft_strchr(OPERATOR, input[data->subber]))
		data->subber++;
	while (input[data->subber] && (!ft_strchr(OPERATOR, input[data->subber])))
		data->subber++;
	tmp1 = ft_strsub(input, data->index, (data->subber - data->index));
	if (!ft_isstrprint(tmp = ft_strtrim(tmp1)))
	{
		ft_strdel(&tmp);
		ft_strdel(&tmp1);
		return (0);
	}
	if (ft_strchr(OPERATOR, tmp[0]))
		return (0);
	if (input[data->subber] == '\0')
		data->wordsize = ft_strlen(tmp);
	ft_strdel(&tmp);
	ft_strdel(&tmp1);
	return (1);
}

void			link_last_node(char *input, t_lexit **list, t_parsing *data)
{
	char 		*content;
	t_lexit		*tmp;

	tmp = *list;
	content = ft_strsub(input, (data->index + 1), (data->subber - data->index));
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = add_node(content, data->env);
	ft_strdel(&content);
	tmp->next->prev = tmp;
}

void			link_nodes(char *input, t_lexit **list, t_parsing *data)
{
	char 		*content;
	t_lexit		*tmp;

	tmp = *list;
	data->index--;
	content = ft_strsub(input, data->anex, data->check);
	data->anex = data->index + 1;
	if (!tmp)
	{
		*list = add_node(content, data->env);
		ft_strdel(&content);
		tmp = *list;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add_node(content, data->env);
		ft_strdel(&content);
		tmp->next->prev = tmp;
	}
	if (ft_strchr(OPERATOR, data->to_node_op[0]))
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add_node(data->to_node_op, data->env);
		tmp->next->prev = tmp;
		data->to_node_op[0] = '\0';
		data->to_node_op[1] = '\0';
	}
	if (input[data->subber] == '\0')
		link_last_node(input, list, data);
	data->index++;
}

int				node_lro(char *input, t_lexit **list, t_parsing *data)
{
	if (!check_left_right(input, data))
		return (0);
	link_nodes(input, list, data);
	return (1);
}

int				check_if_over(char *input, t_parsing *data)
{
	char		*tmp;
	char		*tmp1;
	int		start;

	tmp = NULL;
	tmp1 = NULL;
	start = 0;
	if (input[data->index + 1] == '\0')
		return (1);
	else
		start = data->index + 1;
	data->subber = data->index;
	while (data->subber < data->len)
	{
		data->subber++;
		data->last++;
	}
	tmp1 = ft_strsub(input, start, data->last);
	if (!ft_isstrprint(tmp = ft_strtrim(tmp1)))
	{
		ft_strdel(&tmp);
		ft_strdel(&tmp1);
		data->last = 0;
		return (1);
	}
	// ft_putstr("OUESHJ");
	if (ft_strchr(OPERATOR, tmp[0]))
		return (-1);
	ft_strdel(&tmp);
	ft_strdel(&tmp1);
	data->last = 0;
	return (0);
}

void			last_node(t_lexit **list, char *input, t_parsing *data)
{
	int		i;
	int		j;
	t_lexit	*tmp;
	char		*tmpn;
	char		*content;

	tmp = *list;
	i = data->index - 1;
	j = 0;
	while (i > 0)
	{
		if (ft_strchr(OPERATOR, input[i - 1]))
			break ;
		i--;
		j++;
	}
	tmpn = ft_strsub(input, i, j);
	content = ft_strtrim(tmpn);
	if (!tmp)
	{
		*list = add_node(content, data->env);
		ft_strdel(&tmpn);
		ft_strdel(&content);
		tmp = *list;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add_node(content, data->env);
		ft_strdel(&content);
		ft_strdel(&tmpn);
		tmp->next->prev = tmp;
	}
}

int				test_l_r(t_parsing *data, char *input, t_lexit **list)
{
	int			ret;

	ret = 0;
	if ((data->ptr = ft_strchr(OPERATOR, input[data->index])))
	{
		data->to_node_op[0] = data->ptr[0];
		get_full_op(data, input);
		if (data->ptr[0] != ';')
			 if(!node_lro(input, list, data))
					return(-1);
		if (data->ptr[0] == ';')
		{
			if ((ret = check_if_over(input, data)) != -1)
				last_node(list, input, data);
			else if (ret == -1)
				return (ret);
			if (ret == 0)
				node_lro(input, list, data);
		}
	}
	return (0);
}

int				parsing_listing(t_lexit **list, char *input, t_env *env, t_sh *sh)
{
	t_parsing	*data;
	t_lexit		*tmp;
	char			*empty;

	tmp = *list;
	data = init_data();
	data->env = env;
	empty = ft_strtrim(input);
	if (empty[0] == '\0')
		data->empty = 1;
	ft_strdel(&empty);
	data->len = ft_strlen(input);
	if (quote_checker(data, input, sh) && !data->empty)
	{
		while (input[++data->index])
			if ((test_l_r(data, input, list) == -1))
				return(ft_errors(1, &data->ptr[0], NULL));
		if (input && !*(list))
			tmp = single_node(tmp, list, env, input);
	}
	ft_memdel((void **)&data);
	return (1);
}
