/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 17:30:32 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/27 17:31:42 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

t_lexit		*ft_tree_it(t_lexit *list, t_lexit *delim, int prio)
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
		return (ft_tree_it(list, delim, prio + 1));
}
