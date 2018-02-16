/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 22:04:38 by rfabre            #+#    #+#             */
/*   Updated: 2016/12/06 20:41:53 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;

	i = -1;
	while (++i < len)
	{
		if (*(src + i))
			*(dst + i) = *(src + i);
		else
			while (i < len)
				*(dst + i++) = '\0';
	}
	return (dst);
}
