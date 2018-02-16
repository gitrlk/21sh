/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 23:06:29 by rfabre            #+#    #+#             */
/*   Updated: 2016/12/06 23:30:14 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	t_list *atemp;

	if (f == NULL)
		return ;
	while (lst != NULL)
	{
		atemp = lst->next;
		f(lst);
		lst = atemp;
	}
}
