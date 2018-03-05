/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:16:14 by jecarol           #+#    #+#             */
/*   Updated: 2018/03/05 18:41:25 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"


void				ft_resize(int i)
{
	struct winsize	sz;

	(void)i;
	ioctl(STDERR_FILENO, TIOCGWINSZ, &sz);
	g_data->win_col = sz.ws_col;
	g_data->win_line = sz.ws_row;
	tputs(tgetstr("cl", NULL), 1, ft_pointchar);
	ft_prompt();
	ft_putstr(g_data->line);
}



void		ft_init(void)
{
	char			*name_term;

	if ((name_term = getenv("TERM")) == NULL)
		ft_putendl("<TERM> VARIABLE NOT FOUND");
	if (tgetent(NULL, name_term) == ERR)
		ft_putendl("VARIABLE NOT VALID");
	if (tcgetattr(0, &g_data->save_term) == -1)
		ft_putendl("SAVING TERM FAILED");
	if (tcgetattr(0, &g_data->term) == -1)
		ft_putendl("SAVING TERM FAILED");
	g_data->term.c_lflag &= ~(ICANON);
	g_data->term.c_lflag &= ~(ECHO);
	g_data->term.c_cc[VMIN] = 1;
	g_data->term.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &g_data->term);
	tputs(tgetstr("ti", NULL), 1, ft_pointchar);
	ft_resize(1);
}

int				ft_pointchar(int c)
{
	write(STDIN_FILENO, &c, 1);
	return (0);
}

void			ft_prompt(void)
{
	ft_putstr(TURQUOISE);
	ft_putstr("$>");
	ft_putstr(DEFAULT);
}
