/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:30:17 by jecarol           #+#    #+#             */
/*   Updated: 2016/12/07 15:17:05 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memset(void *b, int c, size_t len)
{
	char	*str;
	size_t	j;

	j = 0;
	str = (char *)b;
	while (j < len)
	{
		str[j] = (unsigned char)c;
		j++;
	}
	return ((void*)b);
}
