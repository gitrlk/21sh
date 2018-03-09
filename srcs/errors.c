/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:00 by jecarol           #+#    #+#             */
/*   Updated: 2018/03/08 22:37:21 by jecarol          ###   ########.fr       */
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
		ft_putchar('\n');
		ft_putstr_fd("21sh: parse error near `<'\n", 2);
		return (0);
	}
	if (code == 2)
	{
		ft_putchar('\n');
		ft_putstr_fd("21sh: parse error near `>'\n", 2);
		return (0);
	}
	if (code == 3)
	{
		ft_putchar('\n');
		ft_putstr_fd("21sh: parse error near `;;'\n", 2);
		return (0);
	}
	if (code == 4)
	{
		ft_putchar('\n');
		ft_putstr_fd("21sh: parse error near `newline'\n", 2);
		return (0);
	}
	if (code == 5)
	{
		ft_putchar('\n');
		ft_putstr_fd("21sh: parse error near `;|'\n", 2);
		return (0);
	}
	if (code == 6)
	{
		ft_putchar('\n');
		ft_putstr_fd("21sh: parse error near `;'\n", 2);
		return (0);
	}
	if (code == 7)
	{
		ft_putchar('\n');
		ft_putstr_fd("21sh: ", 2);
		ft_putstr(cmd);
		ft_putstr_fd(" command not found.\n", 2);
		return (0);
	}
	return (1);
}
