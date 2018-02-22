#include "../includes/sh.h"

int 			ft_errors(int code, char *cmd, char *arg)
{
	if (!cmd)
		(void)cmd;
	if (!arg)
		(void)arg;
	if (code == 1)
	{
		ft_putchar('\n');
		ft_putstr_fd("21sh: parse error near `<'", 2);
		return (0);
	}
	if (code == 2)
	{
		ft_putchar('\n');
		ft_putstr_fd("21sh: parse error near `>'", 2);
		return (0);
	}
	if (code == 3)
	{
		ft_putchar('\n');
		ft_putstr_fd("21sh: parse error near `;;'", 2);
		return (0);
	}
	if (code == 4)
	{
		ft_putchar('\n');
		ft_putstr_fd("21sh: parse error near `newline'", 2);
		return (0);
	}
	if (code == 5)
	{
		ft_putchar('\n');
		ft_putstr_fd("21sh: parse error near `;|'", 2);
		return (0);
	}
	if (code == 6)
	{
		ft_putchar('\n');
		ft_putstr_fd("21sh: parse error near `;'", 2);
		return (0);
	}
	return (1);
}

void			ft_freetab(char **table)
{
	int			i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
	{
		ft_strdel((&table[i]));
		i++;
	}
	ft_memdel((void **)&table);
}

void			ft_line_reset(t_edit *line)
{
	ft_strdel(&line->line);
	free(line->line);
	line->cursor_pos = 2;
	line->max_size = 2;
	line->line = ft_memalloc(sizeof(char));
	line->select_mode = 0;
	line->curr = NULL;
}

int 				ft_what_op_value_to_know_how_to_execute(char *str, int *i)
{
	if (str[*i] == ';')
		return (SEMICOLON);
	else if (str[*i] == '|')
	{
		if (str[*i+1] == '|')
		{
			*i += 1;
			return (DOUBLEPIPE);
		}
		return (PIPE);
	}
	else if (str[*i] == '>')
	{
		if (str[*i+1] == '>')
		{
			*i += 1;
			return(DOUBLECHEVRONRIGHT);
		}
		return (CHEVRONRIGHT);
	}
	else if (str[*i] == '<')
	{
		if (str[*i+1] == '<')
		{
			*i += 1;
			return(DOUBLECHEVRONLEFT);
		}
		return (CHEVRONLEFT);
	}
	else if (str[*i] == '&')
	{
		if (str[*i+1] == '&')
		{
			*i += 1;
			return (DOUBLESPER);
		}
		return (ESPER);
	}
	else
		return (-1);
}

int 				ft_isstrprint(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		return (ft_isprint(str[i]));
	return (0);
}

char				**ft_prep_input(char *str)
{
	char **tmp;
	char *tmp1;
	int i;

	i = 0;
	tmp = ft_strsplit(str, ' ');
	while (tmp[i])
	{
		tmp1 = ft_strtrim(tmp[i]);
		ft_strdel(&tmp[i]);
		tmp[i] = tmp1;
		i++;
	}
	return (tmp);
}

t_lexit 			*ft_add_token(t_edit *line, int *i, int *j)
{
	t_lexit *tmp;

	if (!(tmp = ft_memalloc(sizeof(t_edit))))
		return (NULL);
	tmp->next = NULL;
	tmp->input = ft_strsub(line->line, *j, *i - *j);
	if (!ft_isstrprint(tmp->input))
	{
		tmp->input = NULL;
		tmp->to_exec = NULL;
	}
	else
	{
		tmp->to_exec = ft_prep_input(tmp->input);
		ft_strdel(&tmp->input);
	}
	tmp->lexem = ft_what_op_value_to_know_how_to_execute(line->line, i);
	return (tmp);
}



void 				ft_tokenize_it(t_edit *line, t_lexit **lexdat)
{
	int i;
	int j;
	t_lexit *tmp;

	i = 0;
	j = 0;
	tmp = *lexdat;
	while (line->line[i])
	{
		if (ft_strchr(OPERATOR, line->line[i]))
		{
			if (!tmp)
			{
				*lexdat = ft_add_token(line, &i, &j);
				tmp = *lexdat;
			}
			else
			{
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = ft_add_token(line, &i, &j);
			}
			j = i + 1;
		}
		i++;
		if (line->line[i] == '\0')
		{
			if (!tmp)
			{
				*lexdat = ft_add_token(line, &i, &j);
				tmp = *lexdat;
			}
			else
			{
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = ft_add_token(line, &i, &j);
			}
		}
		while (ft_isspace(line->line[i]))
			i++;
	}
}

void ft_print_lexdat(t_lexit *lexdat)
{
	t_lexit *tmp;
	int i;

	i = 0;
	tmp = lexdat;
	while (tmp)
	{
		if (tmp->to_exec)
		{
			while (tmp->to_exec[i])
			{
				ft_putstr(tmp->to_exec[i]);
				ft_putchar('\n');
				i++;
			}
			i = 0;
		}
		ft_putstr("LEXEM TO COME HAS VALUE : ");
		ft_putnbr(tmp->lexem);
		ft_putchar('\n');
		tmp = tmp->next;
	}
}

void 				ft_free_lexdat(t_lexit *lexdat)
{
	t_lexit *tmp;

	tmp = lexdat;
	while (lexdat)
	{
		tmp = lexdat;
		lexdat = lexdat->next;
		ft_strdel(&tmp->input);
		ft_freetab(tmp->to_exec);
		ft_freetab(tmp->allpaths);
		free(tmp);
	}
}

int 				ft_pre_parser(t_edit *line)
{
	int i;

	i = 0;
	while (line->line[i])
	{
		if (ft_strchr(OPERATOR, line->line[i]))
		{
			if (line->line[i] == '>')
			{
				if (line->line[i+1] == '<')
					return (1);
				if (line->line[i+1] == ';')
					return (6);
			}
			if (line->line[i] == '<')
			{
				if (line->line[i+1] == '>')
					return (2);
				if (line->line[i+1] == ';')
					return (6);
			}
			if (line->line[i] == ';')
			{
				if (line->line[i+1] == ';')
					return (3);
				if (line->line[i+1] == '|')
					return (5);
			}
		}
		i++;
	}
	return (0);
}

int 				ft_parser(t_lexit *lexdat)
{
	t_lexit *tmp;

	tmp = lexdat;
	while (tmp)
	{
		if (tmp->lexem == 3 || tmp->lexem == 4 || tmp->lexem == 1)
		{
			if (!tmp->next->to_exec)
				return (4);
		}
		tmp = tmp->next;
	}
	return (0);
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

void			ft_init_all_paths(char **paths)
{
	int			i;
	char		*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		i++;
	}
}

char				**ft_set_paths(t_env *env)
{
	t_env *tmp;
	char *tmp1;
	char **apaths;

	tmp = env;
	if (!tmp)
		return (NULL);
	while (tmp)
	{
		if (!ft_strncmp("PATH=", tmp->var, 5))
		{
			tmp1 = ft_strdup(tmp->var + 5);
			apaths = ft_strsplit(tmp1, ':');
			ft_strdel(&tmp1);
			ft_init_all_paths(apaths);
			return (apaths);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char				*find_cmd(char **apaths, char *cmd)
{
	int	i;
	char	*tmp_path;

	i = 0;
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
	return (NULL);
}

void				ft_env(char **cmd, t_env *env)
{
	if (!cmd[1])
		ft_print_env(env);
}

void				ft_execute_non_binary(char **cmd, t_env *env, t_lexit *lexdat, t_edit *line)
{
	if (!ft_strcmp(cmd[0], "env"))
		ft_env(cmd, env);
	if (ft_strequ(cmd[0], "exit"))
	{
		ft_free_lexdat(lexdat);
		ft_line_reset(line);
		exit(0);
	}
}

void				ft_execute_binary(char **cmd, t_env *env, int lexem)
{
	
}

void				ft_execs(t_lexit *lexdat, t_env *env, t_edit *line)
{
	char *path;
	t_lexit *tmp;
	int i;

	i = 0;
	tmp = lexdat;
	lexdat->allpaths = ft_set_paths(env);
	while (tmp)
	{
		if (!(path = find_cmd(lexdat->allpaths, tmp->to_exec[0])))
			ft_execute_non_binary(tmp->to_exec, env, lexdat, line);
		else
			ft_execute_binary(tmp->to_exec, env, tmp->lexem);
		tmp = tmp->next;
	}
}

int				main(int ac, char **av, char **envp)
{

	(void)ac;
	(void)av;

	int buf;
	t_edit *line;
	t_lexit *lexdat;
	int ret;
	int i;
	t_env		*env;
	buf = 0;
	i = 0;
	ret = 0;
	env = NULL;
	lexdat = NULL;
	line = ft_memalloc(sizeof(t_edit));
	line->hstr = NULL;
	ft_line_reset(line);
	line->sz = ft_init(line);
	while (envp[i])
		ft_push_env(&env, envp[i++]);
	while (42)
	{
		ft_prompt();
		while ((ret = read(0, &buf, sizeof(int))) && buf != 10)
		{
			handle_key(buf, line);
			buf = 0;
		}
		if (ft_errors(ft_pre_parser(line), NULL, NULL))
		{
			ft_tokenize_it(line, &lexdat);
			if (ft_errors(ft_parser(lexdat), NULL, NULL))
			{
				ft_putchar('\n');
				ft_execs(lexdat, env, line);
				// ft_putchar('\n');
				// ft_putchar('\n');
				// ft_print_lexdat(lexdat);
			}
		}
		ft_add_history(line); //add line to history
		ft_free_lexdat(lexdat);
		lexdat = NULL;
		if (ft_strequ(line->line, "clear"))
			tputs(tgetstr("cl", NULL), 1, ft_pointchar);
		ft_line_reset(line);
	}
	return 0;
}
