/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:04 by jecarol           #+#    #+#             */
/*   Updated: 2018/04/25 19:17:12 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			ft_print_env(t_env *env)
{
	while (env)
	{
		ft_putendl_fd(env->var, STDOUT_FILENO);
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

int				ft_get_egal_pos(char *vartoadd)
{
	int			i;
	int			result;

	i = 0;
	result = 0;
	if (ft_strchr(vartoadd, '='))
	{
		while (vartoadd[i] != '=')
		{
			i++;
			result++;
		}
		return (result);
	}
	return (0);
}

void			ft_refresh_link(t_env **tmp, char *vartoadd)
{
	t_env		*tmp2;

	tmp2 = *tmp;
	ft_strdel(&tmp2->var);
	tmp2->var = ft_strdup(vartoadd);
}

void			ft_refresh_link_cd(t_env **tmp, char *vartoadd)
{
	t_env		*tmp2;
	int			i;

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

void			free_env(t_env *lst)
{
	t_env		*tmp;

	tmp = lst;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		ft_strdel(&tmp->var);
		free(tmp);
	}
}

void			ft_empty_env(t_env **env, int *i)
{
	free_env(*env);
	*env = NULL;
	*i += 1;
}

void			update_list(t_lexit *list, int i, t_env *env)
{
	char		**apaths;
	char		**tmp;
	t_lexit *tmp1;
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

void			exec_env(t_lexit *list, int i, t_env *new_env, t_sh *sh)
{
	update_list(list, i, new_env);
	if (check_if_builtin(list))
		exec_no_fork(list, new_env, sh);
	else if (list->prio != ARG)
		execs(sh->execs, sh->env, sh);
	else
		ft_errors(7, NULL, sh->execs->args[0]);
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
