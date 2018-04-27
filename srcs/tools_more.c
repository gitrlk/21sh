/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_more.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:49:57 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/28 01:50:09 by rlkcmptr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

t_lexit			*copy_segment(t_sh *sh, t_lexit *src)
{
	t_lexit		*dst;

	dst = add_node(src->input, sh);
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
