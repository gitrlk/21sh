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

int		ft_cnt_parts(const char *s, char c, char d, char e)
{
	int		cnt;
	int		in_substring;
	int		i;

	i = 0;
	in_substring = 0;
	cnt = 0;
	while (i < ((int)ft_strlen(s)))
	{
		if (s[i] == d)
		{
			i++;
			while (s[i] != d)
			{
				if (s[i] == '\0')
				{
					cnt--;
					break ;
				}
				i++;
			}
			cnt++;
		}
		if (s[i] == e)
		{
			i++;
			while (s[i] != e)
			{
				if (s[i] == '\0')
				{
					cnt--;
					break ;
				}
				i++;
			}
			cnt++;
		}
		if (in_substring == 1 && s[i] == c)
			in_substring = 0;
		if (in_substring == 0 && s[i] != c && s[i] != d && s[i] != e)
		{
			in_substring = 1;
			cnt++;
		}
		i++;
	}
	return (cnt);
}

int		ft_wlen(const char *s, char c)
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

int				is_quote_closed(char const *s, char quote)
{
	int			i;

	i = 1;
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote)
		return (1);
	return(0);
}

char			**ft_strsplit_21(char const *s, char c, char d, char e)
{
	char	**t;
	int		nb_word;
	int		index;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	index = 0;
	nb_word = ft_cnt_parts((const char *)s, c, d, e);
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
			if (is_quote_closed(s, d))
			{
				s++;
				t[index] = ft_strsub((const char *)s, 0, ft_wlen((const char *)s, d));
				index++;
				s = s + ft_wlen(s, d);
				s++;
			}
			else
			{
				t[index] = ft_strdup(&d);
				index++;
			}
		}
		else if (*s == e)
		{
			if (is_quote_closed(s, e))
			{
				s++;
				t[index] = ft_strsub((const char *)s, 0, ft_wlen((const char *)s, e));
				index++;
				s = s + ft_wlen(s, e);
				s++;
			}
			else
			{
				t[index] = ft_strdup(&e);
				index++;
			}
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
	char	*may;
	struct stat	s;


	i = 0;
	may = NULL;
	if (!access(cmd, F_OK))
	{
		if (lstat(cmd, &s) != -1 && !(S_ISDIR(s.st_mode)) && !access(cmd, X_OK) && !ft_strstr(BUILTIN, cmd))
		{
			may = ft_strdup(cmd);
			return (may);
		}
	}
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
