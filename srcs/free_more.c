/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 17:35:24 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/27 17:35:25 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			free_env(t_env *lst)
{
	t_env		*tmp;

	tmp = lst;
	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		ft_strdel(&tmp->var);
		free(tmp);
	}
}
