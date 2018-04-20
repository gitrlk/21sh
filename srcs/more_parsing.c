#include "../includes/sh.h"

int				check_semi(t_sh *sh, t_lexit *lst)
{
	t_lexit		*tmp;
	int			i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		if (tmp->prio == SEMICOLON)
			return (1);
		if (!tmp->next)
		{
			sh->execs = sh->list;
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int			get_number(t_sh *sh)
{
	char		**tmp;
	int			i;

	i = 0;
	tmp = ft_strsplit(sh->line->line, ';');
	while (tmp[i])
		i++;
	ft_freetab(tmp);
	return (i);
}

t_lexit			*copy_segment(t_sh *sh, t_lexit *src)
{
	t_lexit		*dst;

	dst = add_node(src->input, sh);
	dst->redirs = src->redirs;
	return (dst);
}

int					check_pipe(t_lexit *node, int checker)
{
	if (!checker && (node->prev->prio != COMMAND || node->next->prio != COMMAND))
		return (node->prev->prio != COMMAND ?
	ft_errors(6, NULL, node->prev->args[0]) :
	ft_errors(6, NULL, node->next->args[0]));
	return (1);
}

int					check_redirr(t_lexit *node, int checker)
{
	if (!checker)
		return (ft_errors(6, NULL, node->prev->args[0]));
	return (1);
}

int					check_redirl(t_lexit *node)
{
	if ((open(node->next->args[0], O_RDONLY)) == -1)
		return(ft_errors(4, NULL, node->next->args[0]));
	return (1);
}

int 				double_check(t_lexit *lst)
{
	int checker;
	t_lexit *tmp;

	checker = 0;
	tmp = lst;
	if (tmp)
	{
		while(tmp)
		{
			if (tmp->prio == COMMAND)
				checker = 1;
			if (tmp->prio == PIPE)
				if (!check_pipe(tmp, checker))
					return (0);
			if (tmp->prio == REDIR_R || tmp->prio == REDIR_RR)
				if (!check_redirr(tmp, checker))
					break ;
			if (tmp->prio == REDIR_L)
				if (!check_redirl(tmp))
					break ;
			tmp = tmp->next;
		}
		if (!tmp)
			return (1);
	}
	return (0);
}
