/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:05 by jecarol           #+#    #+#             */
/*   Updated: 2018/04/27 03:48:02 by rlkcmptr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int				get_more_prio(char *str)
{
	if ((ft_isstrprint(str)) && (!ft_strcmp(str, ">") ||
	(str[0] == '>' && str[1] == '&') ||
	(str[1] == '>' && str[2] == '&')))
		return (REDIR_R);
	else if (!ft_strcmp(str, ">>"))
		return (REDIR_RR);
	else if (!ft_strcmp(str, "<"))
		return (REDIR_L);
	else if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	else if (ft_isstrprint(str))
		return (ARG);
	else
		return (-1);
}

int				get_prio(char *str, char **command, char **apaths)
{
	char			*path;

	if (!str)
		return (ERROR);
	if (!ft_strcmp(str, ";"))
		return (SEMICOLON);
	else if (!ft_strcmp(str, "&&") || !ft_strcmp(str, "||"))
		return (AND_OR);
	else if (!ft_strcmp(str, "|"))
		return (PIPE);
	else if ((path = find_cmd(apaths, str)) || !ft_strcmp(str, "cd") ||
	!ft_strcmp(str, "env") || !ft_strcmp(str, "echo") || !ft_strcmp(str, "exit")
	||  !ft_strcmp(str, "setenv") || !ft_strcmp(str, "unset"))
	{
		if (path)
		{
			*command = ft_strdup(path);
			ft_strdel(&path);
		}
		else
			*command = ft_strdup(str);
		return (COMMAND);
	}
	return (get_more_prio(str));
}

char				**ft_prep_input(char *str)
{
	char			**tmp;

	tmp = ft_strsplit_21(str, ' ', '\'', '\"');
	return (tmp);
}
