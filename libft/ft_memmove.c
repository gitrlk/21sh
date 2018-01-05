/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 16:09:09 by jecarol           #+#    #+#             */
/*   Updated: 2016/12/07 15:22:39 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dst2;
	char	*src2;

	dst2 = (char *)dst;
	src2 = (char *)src;
	i = 0;
	if (src2 < dst2)
	{
		while ((int)--len >= 0)
			dst2[len] = src2[len];
	}
	else
		while (i < len)
		{
			dst2[i] = src2[i];
			i++;
		}
	return (dst2);
}
