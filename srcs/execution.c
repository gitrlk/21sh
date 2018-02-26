/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:03 by jecarol           #+#    #+#             */
/*   Updated: 2018/02/26 20:51:47 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

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

void				ft_execute_non_binary(char **cmd, t_env *env, t_lexit *lexdat,
					t_edit *line)
{
	(void)lexdat;
	(void)line;

	if (!ft_strcmp(cmd[0], "env"))
		ft_env(cmd, env);
	if (ft_strequ(cmd[0], "exit"))
	{
		ft_free_lexdat(lexdat);
		ft_line_reset(line);
		exit(0);
	}
}

void				ft_execute_binary(char **cmd, t_env *env, int lexem, char *path)
{
	pid_t		pid;
	char		**newenvp;

	(void)lexem;
	newenvp = ft_fill_envp(env);
	pid = fork();
	if (!pid)
		execve(path, cmd, newenvp);
	else if (pid > 0)
		wait(NULL);
	ft_freetab(newenvp);
}

void				ft_execs(t_lexit *lexdat, t_env *env, t_edit *line)
{
	char *path;
	t_lexit *tmp;
	int i;

	i = 0;
	tmp = lexdat;
	if (tmp)
	{
		lexdat->allpaths = ft_set_paths(env);
		while (tmp)
		{
			if (tmp->to_exec)
			{
				if (!(path = find_cmd(lexdat->allpaths, tmp->to_exec[0])))
					ft_execute_non_binary(tmp->to_exec, env, lexdat, line);
				else
					ft_execute_binary(tmp->to_exec, env, tmp->lexem, path);
				ft_strdel(&path);
			}
			tmp = tmp->next;
		}
	}
}
