/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:05:56 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/27 18:07:35 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int			check_if_env(char *venv, char *str)
{
	int		len;

	len = ft_strlen(str);
	if (!ft_strncmp(venv, str, len))
		if (!ft_strncmp((venv + len), "=", 1))
			return (1);
	return (0);
}

char		*get_venv_value(t_env **venv, char *search)
{
	t_env	*tmp;

	tmp = *venv;
	while (tmp)
	{
		if (find_t_env_str(tmp->var, search))
			return (tmp->var + (ft_strlen(search) + 1));
		tmp = tmp->next;
	}
	return (NULL);
}

int			exec_cd_env(t_env **env, char *search, int mode, char **args)
{
	t_env	*tmp;
	char	*path;

	tmp = *env;
	while (tmp)
	{
		if (check_if_env(tmp->var, search))
		{
			if (mode == 3)
			{
				path = ft_strjoin(get_venv_value(&tmp, search), (args[1] + 1));
				do_cd(path, env, mode);
				ft_strdel(&path);
			}
			else
				do_cd(get_venv_value(&tmp, search), env, mode);
			return (0);
		}
		tmp = tmp->next;
	}
	if (mode == 1 || mode == 3)
		ft_putendl_fd("cd : HOME not set", 2);
	else if (mode == 2)
		ft_putendl_fd("cd : OLDPWD not set", 2);
	return (1);
}

void		ft_refresh_link_cd(t_env **tmp, char *vartoadd)
{
	t_env	*tmp2;
	int		i;

	i = 0;
	tmp2 = *tmp;
	while (tmp2)
	{
		if (!ft_strncmp(tmp2->var, vartoadd, 7))
		{
			ft_strdel(&tmp2->var);
			tmp2->var = ft_strdup(vartoadd);
			i = 1;
		}
		tmp2 = tmp2->next;
	}
	if (!i)
		ft_push_env(tmp, vartoadd);
}
