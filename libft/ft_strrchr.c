/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:48:44 by rfabre            #+#    #+#             */
/*   Updated: 2016/12/07 00:14:11 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (ptr[i])
		i++;
	if ((char)c == ptr[i])
		return (&ptr[i]);
	i--;
	while (ptr[i])
	{
		if (c == ptr[i])
			return (&ptr[i]);
		i--;
	}
	return (NULL);
}
