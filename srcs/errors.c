/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:00 by jecarol           #+#    #+#             */
/*   Updated: 2018/04/23 16:11:23 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int 			ft_errors(int code, char *cmd, char *arg)
{
	if (!cmd)
		(void)cmd;
	if (!arg)
		(void)arg;
	if (code == 1)
	{
		ft_putstr_fd("21sh: parse error near `", 2);
		ft_putchar_fd(cmd[0], 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	if (code == 2)
	{
		ft_putstr_fd("21sh: unmatched '\n", 2);
		return (0);
	}
	if (code == 3)
	{
		ft_putstr_fd("21sh: unmatched \"\n", 2);
		return (0);
	}
	if (code == 4)
	{
		ft_putstr_fd("21sh: no such file or directory: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putchar('\n');
		return (0);
	}
	if (code == 5)
	{
		ft_putstr_fd("21sh: permission denied: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putchar('\n');
	}
	if (code == 6)
	{
		ft_putstr_fd("21sh: command not found: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putchar('\n');
		return (0);
	}
	if (code == 7)
	{
		ft_putstr_fd("env: command not found: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putchar('\n');
	}
	if (code == 8)
	{
		ft_putendl_fd(cmd, 2);
		exit(0);
	}
	if (code == 9)
	{
		ft_putstr_fd("cd: permission denied for oldpwd", 2);
		ft_putchar('\n');
		return (0);
	}
	return (1);
}
