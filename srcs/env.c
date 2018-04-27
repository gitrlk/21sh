/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:04 by jecarol           #+#    #+#             */
/*   Updated: 2018/04/27 18:14:55 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			ft_empty_env(t_env **env, int *i)
{
	free_env(*env);
	*env = NULL;
	*i += 1;
}

void			ft_env(t_lexit *l, t_env *env, t_sh *sh)
{
	t_env		*new_env;
	int			i;

	i = 1;
	new_env = (env ? ft_copy_list(env) : NULL);
	if (!l->args[i])
		ft_print_env(new_env);
	else
	{
		if (!ft_strcmp(l->args[i], "-i"))
			ft_empty_env(&new_env, &i);
		if (l->args[i] && l->args[i][0] != '=' && ft_strchr(l->args[i], '='))
			ft_env_with_var(&new_env, l->args[i++]);
		if (l->args[i])
			exec_env(l, i, new_env, sh);
		else
			ft_print_env(new_env);
	}
	if (new_env)
		free_env(new_env);
}
