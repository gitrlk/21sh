/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 19:18:16 by jecarol           #+#    #+#             */
/*   Updated: 2016/12/08 19:18:17 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *list2;

	if (f && lst)
	{
		list2 = f(lst);
		if (list2 && lst->next)
			list2->next = ft_lstmap(lst->next, f);
		return (list2);
	}
	return (NULL);
}
