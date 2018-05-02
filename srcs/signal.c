/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:43:57 by rfabre            #+#    #+#             */
/*   Updated: 2018/05/02 13:45:11 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void				sig_int(int i)
{
	i = 0;
}

void				listen_signal(void)
{
	// signal(SIGINT, sig_int);
}

void				hd_sig(t_hdc *valhd, t_lexit *list, t_sh *sh)
{
	close(valhd->ret_stop[0]);
	ft_strdel(&list->redirs->endoff);
	valhd->ret_stop[0] = open(sh->hd_state, O_RDONLY | O_WRONLY | O_TRUNC);
	close(valhd->ret_stop[0]);
	valhd->ret_stop[1] = 1;
	sh->line->prompt_mode = 0;
	set_term_back();
}

void				init_term(void)
{
	const char		*name;
	struct termios	term;

	name = getenv("TERM");
	if (!name || ft_strcmp(name, "xterm-256color"))
		ft_errors(8,
		"terminal can't be set : couldn't resolve TERM variable", NULL);
	if (tgetent(NULL, name) == ERR)
		ft_errors(8, "terminal can't be set : term unknow", NULL);
	if (tcgetattr(0, &term) == -1)
		ft_errors(8, "tcgetattr", NULL);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VEOF] = 4;
	term.c_cc[VINTR] = 2;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		ft_errors(8, "tcgetattr", NULL);
}

void				set_term_back(void)
{
	const char		*name;
	struct termios	term;

	if (!(name = getenv("TERM")))
		ft_errors(8, "terminal can't be set : specify \"TERM\" variable", NULL);
	if (tgetent(NULL, name) <= 0)
		ft_errors(8, "terminal can't be set : term unknow", NULL);
	if (tcgetattr(0, &term) == -1)
		ft_errors(8, "tcgetattr", NULL);
	term.c_lflag |= (ECHO);
	term.c_lflag |= (ICANON);
	term.c_lflag &= ~(ECHOCTL);
	term.c_cc[VMIN] = 1;
	term.c_cc[VEOF] = 4;
	term.c_cc[VINTR] = 3;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		ft_errors(8, "tcgetattr", NULL);
}
