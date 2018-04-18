#include "../includes/sh.h"

void				cut_list(t_sh *sh, t_execs *igo)
{
	if (!igo->copy)
	{
		igo->copy = copy_segment(sh, igo->tmp);
		igo->copy->first = 1;
		igo->head = igo->copy;
	}
	else
	{
		igo->copy->next = copy_segment(sh, igo->tmp);
		igo->copy->next->first = 0;
		igo->copy->next->prev = igo->copy;
		igo->copy = igo->copy->next;
	}
}

char			**ft_fill_envp(t_env *env)
{
	char		**ret;
	t_env		*tmp;
	int			len;
	int			i;

	tmp = env;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	ret = ft_memalloc(sizeof(char **) * (len + 1));
	i = 0;
	tmp = env;
	while (i < len)
	{
		ret[i] = ft_strdup(tmp->var);
		tmp = tmp->next;
		i++;
	}
	return (ret);
}

char				*find_cmd(char **apaths, char *cmd)
{
	int	i;
	char	*tmp_path;

	i = 0;
	if (apaths)
	{
		while (apaths[i])
		{
			tmp_path = ft_strjoin(apaths[i], cmd);
			if (!access(tmp_path, F_OK) && !ft_strstr(BUILTIN, cmd))
			{
				ft_strdel(&tmp_path);
				return (ft_strjoin(apaths[i], cmd));
			}
			ft_strdel(&tmp_path);
			i++;
		}
	}
	return (NULL);
}

t_lexit			*add_node(char *input, t_env *env)
{
	t_lexit		*tmp;
	char			**apaths;

	apaths = ft_set_paths(env);
	if (!input)
		return (NULL);
	if (!(tmp = ft_memalloc(sizeof(t_lexit))))
		return (NULL);
	tmp->next = NULL;
	tmp->left = 0;
	tmp->right = 0;
	tmp->input = ft_strtrim(input);
	tmp->args = ft_prep_input(input);
	tmp->redirs = NULL;
	tmp->checker = 0;
	tmp->agr = 0;
	tmp->is_pipe = 0;
	tmp->fdsrc = 1;
	tmp->fddst = -1;
	tmp->fdclose = 0;
	tmp->command = NULL;
	tmp->prio = get_prio(tmp->args[0], &tmp->command, apaths);
	ft_freetab(apaths);
	return (tmp);
}

void				get_full_op(t_parsing *data, char *input)
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
		if (data->to_node_op[0] == '<')
				if (input[data->index + 1] == '<')
				{
					data->to_node_op[1] = '<';
					data->index++;
				}
}
