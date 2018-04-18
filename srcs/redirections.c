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
	// node->redirs->follow_up = NULL;

	node->redirs->endoff = ft_strdup(node->next->args[0]);
	do_heredoc(node, sh);
}

void				init_redirs(t_lexit *node)
{
	node->redirs = (t_redir *)malloc(sizeof(t_redir));
	node->checker = 1;
	node->redirs->redir_right = 0;
	node->redirs->redir_left = 0;
	node->redirs->right_target = NULL;
	node->redirs->left_target = NULL;
	node->redirs->endoff = NULL;
	// node->redirs->follow_up = NULL;
}

void				get_std_sd(t_lexit *node)
{
	if (node->args && ft_isdigit(node->args[0][0]))
		node->prev->fdsrc = ft_atoi(node->args[0]);
	if (node->next && node->next->args)
	{
		if (node->next->args[0][0] == '-')
			node->prev->fdclose = 1;
		if (ft_isdigit(node->next->args[0][0]))
			node->prev->fddst = ft_atoi(node->next->args[0]);
	}
}

void				get_last_redir(t_lexit *node, t_sh *sh)
{
	t_lexit		*tmp;

	tmp = node;
	init_redirs(node->prev);
	while (tmp && (tmp->prio != SEMICOLON && tmp->prio != AND_OR && tmp->prio !=
	PIPE && tmp->prio != COMMAND))
	{
		if (tmp->next && ((tmp->prio == REDIR_R || tmp->prio == REDIR_RR)))
		{
			node->prev->redirs->redir_right = tmp->prio == REDIR_R ? 1 : 2;
			if (node->prev->redirs->right_target)
				ft_strdel(&node->prev->redirs->right_target);
			node->prev->redirs->right_target = ft_strdup(tmp->next->input);
			get_std_sd(node);
		}
		if (tmp->next && ((tmp->prio == REDIR_L || tmp->prio == HEREDOC)))
		{
			node->prev->redirs->redir_left = tmp->prio == REDIR_L ? 1 : 2;
			if (tmp->prio == HEREDOC)
				get_eof(tmp, sh);
			if (node->prev->redirs->left_target)
				ft_strdel(&node->prev->redirs->left_target);
			node->prev->redirs->left_target = ft_strdup(tmp->next->input);
		}
		tmp = tmp->next;
	}
}


void				get_redir(t_lexit *node, t_sh *sh)
{
	t_lexit		*tmp;

	tmp = node;
	if (tmp->next && (tmp->next->prio == REDIR_R || tmp->next->prio == REDIR_L ||
	tmp->next->prio == REDIR_RR || tmp->next->prio == HEREDOC))
		get_last_redir(tmp->next, sh);
}

void				assign_redir(t_lexit *list, t_sh *sh)
{
	t_lexit 		*tmp;

	tmp = list;
	while (tmp && tmp->prio != SEMICOLON)
	{
		if (tmp->prio == COMMAND)
			get_redir(tmp, sh);
		tmp = tmp->next;
	}
}

void				do_heredoc(t_lexit *list, t_sh *sh)
{
	t_hdc			valhd;

	init_valhd(&valhd);
	init_term();
	if ((valhd.ret_stop[0] = open("/tmp/heredoc_fd", O_WRONLY |
	O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
		ft_errors(5, NULL, "heredoc error: couldn't create heredoc");
	else
	{
		while (!valhd.ret_stop[1])
		{
			ft_prompt(2);
			ft_line_reset(sh->line);
			while ((valhd.hd = read(0, &sh->buf, sizeof(int))))
			{
				handle_key(sh->buf, sh->line, 1);
				if (sh->buf == '\n' || sh->buf == 3)
					break ;
				sh->buf = 0;
			}
			heredoc_work(sh, list, &valhd);
		}
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
	{
		close(valhd->ret_stop[0]);
		ft_strdel(&list->redirs->endoff);
		valhd->ret_stop[0] = open("/tmp/heredoc_fd",O_RDONLY | O_WRONLY | O_TRUNC);
		close(valhd->ret_stop[0]);
		valhd->ret_stop[1] = 1;
		set_term_back();
	}
	else if (!ft_strcmp(valhd->tmp, list->redirs->endoff))
	{
		ft_strdel(&list->redirs->endoff);
		valhd->ret_stop[1] = 1;
		set_term_back();
	}
	ft_strdel(&valhd->tmp);
	ft_putchar('\n');
}

void				init_valhd(t_hdc *valhd)
{
	valhd->ret_stop[0] = 0;
	valhd->hd = 0;
	valhd->ret_stop[1] = 0;
	valhd->tmp = NULL;
}

void				trim_redir(t_lexit *list)
{
	t_lexit *tmp;
	t_lexit *save;

	tmp = list;
	while (tmp)
	{
		if (tmp->prev && (tmp->prio == REDIR_R || tmp->prio == REDIR_RR ||
		tmp->prio == REDIR_L))
		{
			save = tmp->prev;
			while (tmp->next && tmp->prio != PIPE && tmp->prio != AND_OR &&
			tmp->prio != HEREDOC && tmp->prio != COMMAND)
				tmp = tmp->next;
			if (!tmp->next)
				save->next = NULL;
			else if (tmp->next)
			{
				save->next = tmp;
				tmp->prev = save;
			}
		}
		tmp = tmp->next;
	}
}
