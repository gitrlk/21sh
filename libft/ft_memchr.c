/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 21:37:05 by rfabre            #+#    #+#             */
/*   Updated: 2016/12/06 20:03:35 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*cs;

	cs = (const char *)s;
	i = -1;
	while (++i < n)
		if (*(cs + i) == (char)c)
			return ((void *)cs + i);
	return (NULL);
}
