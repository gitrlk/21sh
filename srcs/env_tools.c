/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:12:42 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/27 18:13:59 by rfabre           ###   ########.fr       */
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

void			update_list(t_lexit *list, int i, t_env *env)
{
	char		**apaths;
	char		**tmp;
	t_lexit		*tmp1;

	tmp1 = list;
	apaths = ft_set_paths(env);
	if (tmp1->input)
		ft_strdel(&tmp1->input);
	if (tmp1->command)
		ft_strdel(&tmp1->command);
	tmp1->input = ft_strdup(tmp1->args[i]);
	tmp = copypasta(tmp1->args, i);
	ft_freetab(tmp1->args);
	list->args = copypasta(tmp, 0);
	ft_freetab(tmp);
	tmp1->prio = get_prio(tmp1->args[0], &list->command, apaths);
	if (apaths)
		ft_freetab(apaths);
}

t_env			*ft_copy_list(t_env *env)
{
	t_env		*tmp;
	t_env		*head;
	t_env		*new;

	tmp = env;
	new = ft_memalloc(sizeof(t_env));
	head = new;
	new->var = ft_strdup(tmp->var);
	while (tmp->next)
	{
		new->next = ft_memalloc(sizeof(t_env));
		new->next->var = ft_strdup(tmp->next->var);
		new->next->next = NULL;
		new = new->next;
		tmp = tmp->next;
	}
	return (head);
}

void			ft_env_with_var(t_env **env, char *vartoadd)
{
	t_env		*tmp;
	int			egal;

	tmp = *env;
	egal = ft_get_egal_pos(vartoadd);
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, vartoadd, egal))
		{
			ft_refresh_link(&tmp, vartoadd);
			return ;
		}
		tmp = tmp->next;
	}
	ft_push_env(env, vartoadd);
}
