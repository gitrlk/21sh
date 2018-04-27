/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:04 by jecarol           #+#    #+#             */
/*   Updated: 2018/04/27 02:58:36 by rlkcmptr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			ft_empty_env(t_env **env, int *i)
{
	free_env(*env);
	*env = NULL;
	*i += 1;
}

void			ft_env(t_lexit *list, t_env *env, t_sh *sh)
{
	t_env		*new_env;
	int			i;

	i = 1;
	new_env = (env ? ft_copy_list(env) : NULL);
	if (!list->args[i])
		ft_print_env(new_env);
	else
	{
		if (!ft_strcmp(list->args[i], "-i"))
			ft_empty_env(&new_env, &i);
		if (list->args[i] && list->args[i][0] != '=' && ft_strchr(list->args[i], '='))
			ft_env_with_var(&new_env, list->args[i++]);
		if (list->args[i])
			exec_env(list, i, new_env, sh);
		else
			ft_print_env(new_env);
	}
	if (new_env)
		free_env(new_env);
}
