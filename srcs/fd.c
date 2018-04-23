#include "../includes/sh.h"

int		isnumber(char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
			return (0);
	}
	return (1);
}

void				switch_in_out(t_sh *sh, int in_out, t_lexit *list)
{
	if (in_out == 1)
	{
			sh->fd.saved_out = dup(1);
			dup2(sh->fd.saved_file, 1);
			close(sh->fd.saved_file);
	}
	if (in_out == 2)
	{
		sh->fd.saved_in = dup(0);
		dup2(sh->fd.saved_file, 0);
		close(sh->fd.saved_file);
	}
	if (in_out == 3)
	{
		if (list->fdclose == 1)
		{
			close(0);
			close(list->fdsrc);
		}
	}
}

int				switch_right(t_lexit *list, t_sh *sh, int *mod)
{
	if (list->redirs && (list->redirs->redir_right == 2))
	{
		if ((sh->fd.saved_file = open(list->redirs->right_target, O_WRONLY |
		O_APPEND | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
			return (-1);
		else
			switch_in_out(sh, 1, list);
		*mod = 1;
	}
	if (list->redirs && (list->redirs->redir_right == 1))
	{
		if (!(isnumber(list->redirs->right_target)) && list->redirs->right_target[0] != '-')
		{
			if ((sh->fd.saved_file = open(list->redirs->right_target, O_WRONLY |
			O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
				return (-1);
		}
		else
			switch_in_out(sh, 3, list);
		switch_in_out(sh, 1, list);
		*mod = 1;
	}
	return (0);
}

int				switch_left(t_lexit *list, t_sh *sh, int *mod)
{
	if (list->redirs && (list->redirs->redir_left == 1))
	{
		if ((sh->fd.saved_file = open(list->redirs->left_target, O_RDONLY)) == -1)
			return (-1);
		else
			switch_in_out(sh, 2, list);
		*mod = *mod == 0 ? 2 : 3;
	}
	if (list->redirs && (list->redirs->redir_left == 2))
	{
		if ((sh->fd.saved_file = open("./.heredoc_fd", O_RDONLY)) == -1)
			return (-1);
		else
			switch_in_out(sh, 2, list);
		*mod = *mod == 0 ? 2 : 3;
	}
	return (0);
}

int				switch_fd(t_lexit *list, t_sh *sh, int *mod)
{
	if ((switch_right(list, sh, mod) == -1))
		ft_errors(5, NULL, list->redirs->right_target);
	if ((switch_left(list, sh, mod) == -1))
		ft_errors(5, NULL, list->redirs->left_target);
	return (*mod);
}

void				reset_fd(t_sh *sh, int mod)
{
	if (mod == 1)
	{
		dup2(sh->fd.saved_out, 1);
		close(sh->fd.saved_out);
	}
	if (mod == 2)
	{
		dup2(sh->fd.saved_in, 0);
		close(sh->fd.saved_in);
	}
	if (mod == 3)
	{
		dup2(sh->fd.saved_out, 1);
		close(sh->fd.saved_out);
		dup2(sh->fd.saved_in, 0);
		close(sh->fd.saved_in);
	}
}
