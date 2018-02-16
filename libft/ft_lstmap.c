/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 23:10:17 by rfabre            #+#    #+#             */
/*   Updated: 2016/12/07 01:51:10 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*list2;

	if (f != NULL && lst != NULL)
	{
		list2 = f(lst);
		if (list2 != NULL && lst->next != NULL)
			list2->next = ft_lstmap(lst->next, f);
		return (list2);
	}
	return (NULL);
}
