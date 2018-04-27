/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:16:14 by jecarol           #+#    #+#             */
/*   Updated: 2018/04/27 19:50:15 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int				ft_pointchar(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (0);
}

void			ft_prompt(int prompt)
{
	if (prompt == 1)
	{
		ft_putstr_fd(TURQUOISE, STDOUT_FILENO);
		ft_putstr_fd("$>", STDOUT_FILENO);
		ft_putstr_fd(DEFAULT, STDOUT_FILENO);
	}
	if (prompt == 2)
	{
		ft_putstr_fd(RED, STDOUT_FILENO);
		ft_putstr_fd("heredoc>", STDOUT_FILENO);
		ft_putstr_fd(DEFAULT, STDOUT_FILENO);
	}
	if (prompt == 3)
	{
		ft_putstr_fd(GREEN, STDOUT_FILENO);
		ft_putstr_fd("quote>", STDOUT_FILENO);
		ft_putstr_fd(DEFAULT, STDOUT_FILENO);
	}
}
