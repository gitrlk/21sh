/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:04 by jecarol           #+#    #+#             */
/*   Updated: 2018/02/26 20:16:30 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			ft_print_env(t_env *env)
{
	while (env)
	{
		ft_putendl(env->var);
		env = env->next;
	}
}

t_env			*add_env(char *var)
{
	t_env		*tmp;

	if (!(tmp = (t_env *)malloc(sizeof(t_env))))
		return (NULL);
	tmp->next = NULL;
	if (!var)
		tmp->var = NULL;
	else
		tmp->var = ft_strdup(var);
	return (tmp);
}

void			ft_push_env(t_env **lst, char *var)
{
	t_env		*tmp;

	tmp = *lst;
	if (!tmp)
		*lst = add_env(var);
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = add_env(var);
	}
}

void				ft_env(char **cmd, t_env *env)
{
	if (!cmd[1])
		ft_print_env(env);
}
