/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 17:48:06 by jecarol           #+#    #+#             */
/*   Updated: 2016/11/28 13:57:41 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char	*l;
	int		i;

	l = (char*)s;
	i = ft_strlen(l);
	while (l[i] != c && i > 0)
		i--;
	if (l[i] == c)
		return (&l[i]);
	return (NULL);
}
