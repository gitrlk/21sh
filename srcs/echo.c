/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:11:43 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/30 16:25:53 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void		print_var(char *var)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (var[i] && var[i] != '=')
		i++;
	j = i;
	while (var[j])
		j++;
	tmp = ft_strsub(var, (i + 1), j - i);
	ft_putstr(tmp);
	ft_strdel(&tmp);
}

int			var_size(char *var)
{
	int i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

void		echo_env(t_lexit *list, int i, t_env **env)
{
	t_env	*tmp;
	char	*envvar;
	char	*checker;

	tmp = (*env);
	checker = NULL;
	if (list->args[i][0] == '$')
	{
		envvar = ft_strsub(list->args[i], 1, (ft_strlen(list->args[i]) - 1));
		while (tmp)
		{
			checker = ft_strsub(tmp->var, 0, var_size(tmp->var));
			if (!ft_strcmp(checker, envvar))
				print_var(tmp->var);
			ft_strdel(&checker);
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
