/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 19:17:48 by jecarol           #+#    #+#             */
/*   Updated: 2016/12/08 19:17:50 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *lst;
	t_list *nxt;

	lst = *alst;
	while (lst)
	{
		nxt = lst->next;
		del(lst->content, lst->content_size);
		free(lst);
		lst = nxt;
	}
	*alst = NULL;
}
