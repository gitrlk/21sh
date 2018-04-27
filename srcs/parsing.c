#include "../includes/sh.h"

t_lexit			*single_node(t_lexit *tmp, t_lexit **list, t_sh *sh, char *input)
{
	*list = add_node(input, sh);
	tmp = *list;
	return (tmp);
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
