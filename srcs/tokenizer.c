/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:05 by jecarol           #+#    #+#             */
/*   Updated: 2018/04/20 20:28:08 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"


int 				ft_isstrprint(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_isprint(str[i]))
		i++;
	return (i);
}

char        **string_to_tab(char *str)
{
	char	**t;

	t = (char **)malloc(sizeof(*t) * 2);
	if (t == NULL)
		return (NULL);
	t[0] = ft_strdup(str);
	// ft_strdel(&str);
	t[1] = NULL;
	return(t);
}

char				**ft_prep_input(char *str)
{
	char			**tmp;
	// char			*tmp1;
	int			i;

	i = 0;
	tmp = ft_strsplit_21(str, ' ', '\'');
	// while (tmp[i])
	// {
	// 	tmp1 = ft_strtrim(tmp[i]);
	// 	ft_strdel(&tmp[i]);
	// 	tmp[i] = tmp1;
	// 	i++;
	// }
	return (tmp);
}

t_lexit 			*ft_tree_it(t_lexit *list, t_lexit *delim, int prio)
{
	t_lexit	*keep;
	t_lexit	*tmp;


	keep = NULL;
	tmp = list;
	if (prio == ERROR || !list)
		return (NULL);
	while (tmp != delim)
	{
		if (tmp->prio == prio)
			keep = tmp;
		tmp = tmp->next;
	}
	if (keep)
	{
		keep->left = ft_tree_it(list, keep, prio);
		keep->right = ft_tree_it(keep->next, delim, prio + 1);
		return (keep);
	}
	else
		return(ft_tree_it(list, delim, prio + 1));
}
