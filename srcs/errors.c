/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:00 by jecarol           #+#    #+#             */
/*   Updated: 2018/03/31 17:34:33 by jecarol          ###   ########.fr       */
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
	}
	return (1);
}
