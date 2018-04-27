/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 17:37:25 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/27 17:38:14 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int			find_t_env(t_env **venv, char *commands)
{
	t_env	*tmp;

	tmp = *venv;
	while (tmp)
	{
		if (find_t_env_array(tmp->var, commands))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int			ft_modify_tenv(t_env **venv, char *new, char *contents)
{
	t_env	*tmp;
	char	*buf;
	t_env	*tmpp;

	tmp = *venv;
	buf = ft_strjoin(new, contents);
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, new, ft_strlen(new)))
		{
			free(tmp->var);
			tmp->var = ft_strdup(buf);
			ft_strdel(&buf);
			return (1);
		}
		tmp = tmp->next;
	}
	if (!(tmpp = ft_memalloc(sizeof(t_env))))
		ft_putendl_fd("malloc failed", 2);
	tmpp->var = ft_strdup(buf);
	ft_lst_add_tenv(venv, tmpp);
	ft_strdel(&buf);
	return (0);
}

void		add_t_env(t_env **venv, char **commands)
{
	t_env	*tmp;
	char	*str_tmp;
	char	*str_buf;

	tmp = ft_memalloc(sizeof(t_env));
	str_buf = ft_strjoin(commands[0], "=");
	str_tmp = ft_strjoin(str_buf, commands[1]);
	ft_strdel(&str_buf);
	tmp->var = ft_strdup(str_tmp);
	ft_strdel(&str_tmp);
	ft_lst_add_tenv(venv, tmp);
}

void		exec_setenv(char **commands, t_env **venv)
{
	int		i;
	char	*tmp;

	i = 0;
	while (commands[i++])
		;
	if (i != 3)
		ft_putendl_fd("setenv usage: setenv <environment variable> <value>", 2);
	else
	{
		if (!find_t_env(venv, commands[0]))
			add_t_env(venv, commands);
		else
		{
			tmp = ft_strjoin((commands[0]), "=");
			ft_modify_tenv(venv, tmp, commands[1]);
			free(tmp);
		}
	}
}
