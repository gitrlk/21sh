/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:49:57 by rfabre            #+#    #+#             */
/*   Updated: 2018/05/03 03:59:43 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

t_lexit			*add_node_proxy(char *input, t_sh *sh)
{
	t_lexit		*tmp;
	char		**apaths;

	if (!input)
		return (NULL);
	if (!(tmp = ft_memalloc(sizeof(t_lexit))))
		return (NULL);
	apaths = ft_set_paths(sh->env);
	tmp->input = ft_strtrim(input);
	tmp->args = ft_prep_input(input);
	replace_quote(tmp, sh);
	init_node(tmp);
	tmp->prio = get_prio(tmp->args[0], &tmp->command, apaths);
	if (tmp->prio != COMMAND && tmp->prio != ARG)
		tmp->prio = ARG;
	ft_freetab(apaths);
	return (tmp);
}

t_lexit			*copy_segment(t_sh *sh, t_lexit *src)
{
	t_lexit		*dst;

	(void)sh;
	dst = ft_memalloc(sizeof(t_lexit));
	dst->input = ft_strdup(src->input);
	dst->args = copypasta(src->args, 0);
	dst->command = ft_strdup(src->command);
	dst->is_pipe = src->is_pipe;
	dst->prio = src->prio;
	dst->first = src->first;
	dst->agr = src->agr;
	dst->checker = src->checker;
	dst->fdsrc = src->fdsrc;
	dst->fddst = src->fddst;
	dst->fdclose = src->fdclose;
	dst->quote = src->quote;
	dst->redirs = src->redirs;
	return (dst);
}

void			cut_list(t_sh *sh, t_execs *igo)
{
	if (!igo->copy)
	{
		igo->copy = copy_segment(sh, igo->tmp);
		igo->copy->first = 1;
		igo->head = igo->copy;
	}
	else
	{
		igo->copy->next = copy_segment(sh, igo->tmp);
		igo->copy->next->first = 0;
		igo->copy->next->prev = igo->copy;
		igo->copy = igo->copy->next;
	}
}

char			*check_on_apaths(char **apaths, char *cmd)
{
	char		*tmp_path;
	int			i;

	i = 0;
	while (apaths[i])
	{
		tmp_path = ft_strjoin(apaths[i], cmd);
		if (!access(tmp_path, F_OK) && !ft_strstr(BUILTIN, cmd))
		{
			ft_strdel(&tmp_path);
			return (ft_strjoin(apaths[i], cmd));
		}
		ft_strdel(&tmp_path);
		i++;
	}
	return (NULL);
}

char			*find_cmd(char **apaths, char *cmd)
{
	char		*may;
	struct stat	s;

	may = NULL;
	if (!ft_strcmp(cmd, "/tmp"))
		return (NULL);
	if (!access(cmd, F_OK))
	{
		if (lstat(cmd, &s) != -1 && !(S_ISDIR(s.st_mode)) &&
		!access(cmd, X_OK) && !ft_strstr(BUILTIN, cmd))
		{
			may = ft_strdup(cmd);
			return (may);
		}
		else
			return (NULL);
	}
	if (apaths)
		return (check_on_apaths(apaths, cmd));
	return (NULL);
}
