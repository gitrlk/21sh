#include "../includes/sh.h"

// t_lexit			*copy_segment(t_sh *sh, t_lexit *src)
// {
// 	t_lexit		*dst;
//
// 	dst = add_node(src->input, sh);
// 	dst->redirs = src->redirs;
// 	return (dst);
// }
//
// void				cut_list(t_sh *sh, t_execs *igo)
// {
// 	if (!igo->copy)
// 	{
// 		igo->copy = copy_segment(sh, igo->tmp);
// 		igo->copy->first = 1;
// 		igo->head = igo->copy;
// 	}
// 	else
// 	{
// 		igo->copy->next = copy_segment(sh, igo->tmp);
// 		igo->copy->next->first = 0;
// 		igo->copy->next->prev = igo->copy;
// 		igo->copy = igo->copy->next;
// 	}
// }
//
// char 				*check_on_apaths(char **apaths, char *cmd)
// {
// 	char	*tmp_path;
//
// 	int i;
// 	i = 0;
// 	while (apaths[i])
// 	{
// 		tmp_path = ft_strjoin(apaths[i], cmd);
// 		if (!access(tmp_path, F_OK) && !ft_strstr(BUILTIN, cmd))
// 		{
// 			ft_strdel(&tmp_path);
// 			return (ft_strjoin(apaths[i], cmd));
// 		}
// 		ft_strdel(&tmp_path);
// 		i++;
// 	}
// 	return (NULL);
// }
//
// char				*find_cmd(char **apaths, char *cmd)
// {
// 	char	*may;
// 	struct stat	s;
//
// 	may = NULL;
// 	if (!access(cmd, F_OK))
// 	{
// 		if (lstat(cmd, &s) != -1 && !(S_ISDIR(s.st_mode)) &&
// 		!access(cmd, X_OK) && !ft_strstr(BUILTIN, cmd))
// 		{
// 			may = ft_strdup(cmd);
// 			return (may);
// 		}
// 	}
// 	if (apaths)
// 		return (check_on_apaths(apaths, cmd));
// 	return (NULL);
// }

void 				add_quote_to_args(char **args, char *str)
{
	int i;

	i = 0;
	if (!args[0])
	{
		args = (char **)malloc(sizeof(char *) * 2);
		args[0] = ft_strdup(str);
		args[1] = NULL;
	}
	else
	{
		while(args[i])
			i++;
		args[i] = ft_strdup(str);
		args[i + 1] = NULL;
	}
}

void			replace_quote(t_lexit *node, t_sh *sh)
{
	int i;

	i = 0;
	while (node->args[i])
	{
		if (node->args[i][0] == '\'' || node->args[i][0] == '\"')
		{
			ft_strdel(&node->args[i]);
			if (sh->line->q_str)
			{
				node->args[i] = ft_strdup(sh->line->q_str);
				ft_strdel(&sh->line->q_str);
			}
		}
		i++;
	}
}

t_lexit			*add_node(char *input, t_sh *sh)
{
	t_lexit		*tmp;
	char		**apaths;
	int			i;

	i = 0;
	if (!input)
		return (NULL);
	if (!(tmp = ft_memalloc(sizeof(t_lexit))))
		return (NULL);
	(void)sh;
	apaths = ft_set_paths(sh->env);
	tmp->input = ft_strtrim(input);
	tmp->args = ft_prep_input(input);
	replace_quote(tmp, sh);
	init_node(tmp);
	tmp->prio = get_prio(tmp->args[0], &tmp->command, apaths);
	ft_freetab(apaths);
	return (tmp);
}

void 			get_full_grtrthn(t_parsing *data, char *input)
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
			get_full_grtrthn(data, input);
		if (data->to_node_op[0] == '<')
				if (input[data->index + 1] == '<')
				{
					data->to_node_op[1] = '<';
					data->index++;
				}
}
