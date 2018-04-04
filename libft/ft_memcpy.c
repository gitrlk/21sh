/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 20:31:31 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/04 16:59:27 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*pt1;
	char	*pt2;

	pt1 = (char *)dst;
	pt2 = (char *)src;
	i = -1;
	while (++i < n)
		*(pt1 + i) = *(pt2 + i);
	return (dst);
}
