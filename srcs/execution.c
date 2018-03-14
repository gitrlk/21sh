/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:03 by jecarol           #+#    #+#             */
/*   Updated: 2018/03/14 19:30:49 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char			**ft_fill_envp(t_env *env)
{
	char		**ret;
	t_env		*tmp;
	int			len;
	int			i;

	tmp = env;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	ret = ft_memalloc(sizeof(char **) * (len + 1));
	i = 0;
	tmp = env;
	while (i < len)
	{
		ret[i] = ft_strdup(tmp->var);
		tmp = tmp->next;
		i++;
	}
	return (ret);
}

char				*find_cmd(char **apaths, char *cmd)
{
	int	i;
	char	*tmp_path;

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
