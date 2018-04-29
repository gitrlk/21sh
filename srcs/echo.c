/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:11:43 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/29 20:29:05 by rlkcmptr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		print_var(char *var)
{
	char *tmp;
	int i;
	int j;

	i = 0;
	j = 0;
	while (var[i] && var[i] != '=')
		i++;
	j = i;
	while (var[j])
		j++;
	tmp = ft_strsub(var, (i+1), j);
	ft_putchar('\n');
	ft_putstr("THIS IS THE VAR : ");
	ft_putstr(tmp);
	ft_strdel(&tmp);
}

void		echo_env(t_lexit *list, int i, t_env **env)
{
	t_env *tmp;
	char *envvar;
	int	checker;

	tmp = (*env);
	checker = 0;
	if (list->args[i][0] == '$')
	{
		envvar = ft_strsub(list->args[i], 1, (ft_strlen(list->args[i])));
		while (tmp)
		{
			if (!ft_strncmp(tmp->var, envvar, ft_strlen(envvar)))
			{
				checker++;
				print_var(tmp->var);
			}
			tmp = tmp->next;
		}
		ft_strdel(&envvar);
	}
	else
		ft_putstr(list->args[i]);
}

void		ft_echo(t_lexit *list, t_env **env)
{
	int		i;

	(void)env;
	if (!list->args[1])
		ft_putchar('\n');
	if (list->args[1])
	{
		i = (ft_strcmp(list->args[1], "-n") == 0 ? 2 : 1);
		while (list->args[i])
		{
			echo_env(list, i, env);
			if (list->args[i + 1])
				write(1, " ", 1);
			i++;
		}
		if (ft_strcmp(list->args[1], "-n") != 0)
			write(1, "\n", 1);
	}
}
