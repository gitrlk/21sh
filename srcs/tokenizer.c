/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 20:15:05 by jecarol           #+#    #+#             */
/*   Updated: 2018/04/25 20:46:46 by jecarol          ###   ########.fr       */
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

char				**ft_prep_input(char *str)
{
	char			**tmp;

	tmp = ft_strsplit_21(str, ' ', '\'', '\"');
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
