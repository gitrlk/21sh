/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:25:09 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/27 21:33:07 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void				get_eof(t_lexit *node, t_sh *sh)
{
	node->redirs = (t_redir *)malloc(sizeof(t_redir));
	node->checker = 1;
	node->redirs->redir_right = 0;
	node->redirs->redir_left = 0;
	node->redirs->right_target = NULL;
	node->redirs->left_target = NULL;
	node->redirs->endoff = NULL;
	node->redirs->endoff = ft_strdup(node->next->args[0]);
	do_heredoc(node, sh);
}

void				do_heredoc(t_lexit *list, t_sh *sh)
{
	t_hdc			valhd;

	init_valhd(&valhd);
	init_term();
	sh->line->prompt_mode = 1;
	sh->buf = 0;
	valhd.ret_stop[0] = open_heredoc(sh);
	while (!valhd.ret_stop[1])
	{
		ft_prompt(2);
		ft_line_reset(sh->line);
		while ((valhd.hd = read(0, &sh->buf, sizeof(int))))
		{
			handle_key(sh);
			if (sh->buf == '\n' || sh->buf == 3 || sh->buf == 4)
				break ;
			sh->buf = 0;
		}
		heredoc_work(sh, list, &valhd);
	}
}

void				heredoc_work(t_sh *sh, t_lexit *list, t_hdc *valhd)
{
	valhd->tmp = ft_strdup(sh->line->line);
	if (ft_strcmp(valhd->tmp, list->redirs->endoff) && (sh->buf != 3))
	{
		ft_putstr_fd(valhd->tmp, valhd->ret_stop[0]);
		ft_putchar_fd('\n', valhd->ret_stop[0]);
	}
	if (sh->buf == 3)
		hd_sig(valhd, list, sh);
	else if (!ft_strcmp(valhd->tmp, list->redirs->endoff) ||
		((sh->buf == 4) && (sh->line->cursor_pos == 2)))
	{
		ft_strdel(&list->redirs->endoff);
		valhd->ret_stop[1] = 1;
		sh->line->prompt_mode = 0;
		set_term_back();
	}
	ft_strdel(&valhd->tmp);
	ft_putchar('\n');
}

void				open_more_hd(t_heredoc *open_hd)
{
	open_hd->tmp = ft_itoa(open_hd->random);
	open_hd->path = ft_freejoinstr(open_hd->path, open_hd->tmp);
	ft_strdel(&open_hd->tmp);
	if ((open_hd->fd = open(open_hd->path, O_WRONLY |
	O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
	{
		open_hd->random++;
		if (open_hd->random > 10)
		{
			ft_strdel(&open_hd->path);
			open_hd->path = ft_strdup("/tmp/.");
		}
	}
}

int					open_heredoc(t_sh *sh)
{
	t_heredoc		open_hd;

	open_hd.path = ft_strdup("/tmp/.");
	open_hd.random = 0;
	open_hd.tmp = NULL;
	open_hd.tmp = 0;
	while (42)
	{
		open_more_hd(&open_hd);
		if ((open_hd.fd != -1) && (open_hd.fd != 0))
		{
			if (sh->hd_state)
				ft_strdel(&sh->hd_state);
			sh->hd_state = ft_strdup(open_hd.path);
			ft_strdel(&open_hd.path);
			break ;
		}
	}
	return (open_hd.fd);
}
