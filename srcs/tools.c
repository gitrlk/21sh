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

static int		ft_cnt_parts(const char *s, char c, char d)
{
	int		cnt;
	int		in_substring;

	in_substring = 0;
	cnt = 0;
	while (*s != '\0')
	{
		if (*s == d)
		{
			s++;
			while (*s != d)
				s++;
			cnt++;
		}
		if (in_substring == 1 && *s == c)
			in_substring = 0;
		if (in_substring == 0 && *s != c && *s != d)
		{
			in_substring = 1;
			cnt++;
		}
		s++;
	}
	return (cnt);
}

static int		ft_wlen(const char *s, char c)
{
	int		len;

	len = 0;
	while (*s != c && *s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

char			**ft_strsplit_21(char const *s, char c, char d)
{
	char	**t;
	int		nb_word;
	int		index;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	index = 0;
	nb_word = ft_cnt_parts((const char *)s, c, d);
	t = (char **)malloc(sizeof(*t) * (nb_word + 1));
	t[nb_word] = NULL;
	if (t == NULL)
		return (NULL);
	while (nb_word--)
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s == d)
		{
			s++;
			t[index] = ft_strsub((const char *)s, 0, ft_wlen((const char *)s, d));
			index++;
			s = s + ft_wlen(s, d);
			s++;
		}
		else
		{
			t[index] = ft_strsub((const char *)s, 0, ft_wlen((const char *)s, c));
			index++;
			s = s + ft_wlen(s, c);
		}
	}
	return (t);
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
// int		count_parts(const char *s, char c)
// {
// 	int		cnt;
// 	int		in_substring;
//
// 	in_substring = 0;
// 	cnt = 0;
// 	while (*s != '\0')
// 	{
// 		if (in_substring == 1 && *s == c)
// 			in_substring = 0;
// 		if (in_substring == 0 && *s != c)
// 		{
// 			in_substring = 1;
// 			cnt++;
// 		}
// 		s++;
// 	}
// 	return (cnt);
// }

// static int		get_parts(const char *s, char c, int pos)
// {
// 	int		cnt;
// 	int 	i;
// 	int		in_substring;
//
// 	i = 0;
// 	in_substring = 0;
// 	cnt = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (in_substring == 1 && s[i] == c)
// 			in_substring = 0;
// 		if (in_substring == 0 && s[i] != c)
// 		{
// 			if (i == 1)
// 				pos = 0;
// 			else
// 				pos = 1;
// 			in_substring = 1;
// 			cnt++;
// 		}
// 		i++;
// 	}
// 	return (cnt);
// }


t_lexit			*add_node(char *input, t_sh *sh)
{
	t_lexit		*tmp;
	char			**apaths;
	int				*array_size;

	char 			**buffer;
	int       i;

	i = 0;
	array_size = 0;
	buffer = NULL;

	if (!input)
		return (NULL);
	if (!(tmp = ft_memalloc(sizeof(t_lexit))))
		return (NULL);

	apaths = ft_set_paths(sh->env);
	// ft_putnbr(sh->line->quote_complete);
	// ft_putendl("quote_complete");
	// if (sh->line->quote_complete && ft_strchr(input,'\''))
	// {
	// 			tmp->input = ft_strtrim(input);
	// 			buffer = split_quote(tmp->input, '\'', sh);
	// 			// ft_putnbr(sh->line->array_size);
	// 			// ft_putendl("NUMBER");
	// 			tmp->args = ft_replace_quote(buffer, sh, tmp->args);
	// 			i = 0;
	// 			tmp->next = NULL;
	// 			tmp->redirs = NULL;
	// 			tmp->checker = 0;
	// 			tmp->agr = 0;
	// 			tmp->is_pipe = 0;
	// 			tmp->fdsrc = 1;
	// 			tmp->fddst = -1;
	// 			tmp->fdclose = 0;
	// 			tmp->command = NULL;
	// 			tmp->prio = get_prio(tmp->args[0], &tmp->command, apaths);
	// 			sh->line->quote_complete = 0;
	// 			ft_freetab(apaths);
	// 			return (tmp);
	// }
	// else
	// {
		tmp->input = ft_strtrim(input);
		tmp->args = ft_prep_input(input);
		tmp->next = NULL;
		tmp->left = 0;
		tmp->right = 0;
		tmp->redirs = NULL;
		tmp->checker = 0;
		tmp->agr = 0;
		tmp->is_pipe = 0;
		tmp->fdsrc = 1;
		tmp->fddst = -1;
		tmp->fdclose = 0;
		tmp->command = NULL;
		tmp->prio = get_prio(tmp->args[0], &tmp->command, apaths);
		// ft_freetab(apaths);
	// }
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
