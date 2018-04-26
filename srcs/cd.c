/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchapka <tchapka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 19:48:20 by tchapka           #+#    #+#             */
/*   Updated: 2018/04/26 19:53:45 by tchapka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/sh.h"

int			find_t_env_str(char *venv, char *str)
{
	int		len;

	len = ft_strlen(str);
	if (!ft_strncmp(venv, str, len))
		if (!ft_strncmp((venv + len), "=", 1))
			return (1);
	return (0);
}

void		cd_success(t_cd *dcd, t_env **env, int mode)
{
	if (dcd->oldpwd)
		ft_modify_tenv(env, "OLDPWD=", dcd->oldpwd);
	if (!(dcd->cwd = getcwd(dcd->tmp, 1024)))
		ft_errors(9, NULL, NULL);
	if (mode == 2)
		ft_putendl(dcd->cwd);
	if (dcd->cwd)
		ft_modify_tenv(env, "PWD=", dcd->cwd);
}

void		do_cd(char *path, t_env **venv, int mode)
{
	t_cd	dcd;

	if (!(dcd.oldpwd = getcwd(dcd.tmp, 1024)))
		ft_errors(9, NULL, NULL);
	if (!access(path, F_OK))
	{
		if (chdir(path) == 0)
			cd_success(&dcd, venv, mode);
		else
			ft_putendl_fd("cd : permission denied", 2);
	}
	else
	{
		ft_putstr_fd("cd : no such file or directory : ", 2);
		ft_putendl_fd(path, 2);
	}
}

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
			return (tmp->var + (ft_strlen(search) +1));
		tmp = tmp->next;
	}
	return (NULL);
}

int			exec_cd_env(t_env **env,char *search, int mode, char **args)
{
	t_env	*tmp;
	tmp =	*env;
	char	*path;

	while (tmp)
	{
		if(check_if_env(tmp->var, search))
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

void		ft_cd(char **args, t_env **env)
{
	if (!args[1] || ft_strequ(args[1], "~") || ft_strequ(args[1], "--"))
		exec_cd_env(env, "HOME", 1, args);
	else if (ft_strequ(args[1], "-"))
		exec_cd_env(env, "OLDPWD", 2, args);
	else if (!ft_strncmp(args[1], "~/", 2))
		exec_cd_env(env, "HOME", 3, args);
	else if (args[1])
		do_cd(args[1], env, 1);
}
