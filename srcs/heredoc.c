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
	else if (!ft_strcmp(valhd->tmp, list->redirs->endoff) || ((sh->buf == 4) && (sh->line->cursor_pos == 2)))
	{
		ft_strdel(&list->redirs->endoff);
		valhd->ret_stop[1] = 1;
		sh->line->prompt_mode = 0;
		set_term_back();
	}
	ft_strdel(&valhd->tmp);
	ft_putchar('\n');
}

int				open_heredoc(t_sh *sh)
{
	int			fd;
	char			*path;
	int			random;
	char			*tmp;

	path = ft_strdup("/tmp/.");
	random = 0;
	while (42)
	{
		tmp = ft_itoa(random);
		path = ft_freejoinstr(path, tmp);
		ft_strdel(&tmp);
		if ((fd = open(path, O_WRONLY |
		O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
		{
			random++;
			if (random > 10)
			{
				ft_strdel(&path);
				path = ft_strdup("/tmp/.");
			}
		}
		else
		{
			if (sh->hd_state)
				ft_strdel(&sh->hd_state);
			sh->hd_state = ft_strdup(path);
			ft_strdel(&path);
			break ;
		}
	}
	return (fd);
}
