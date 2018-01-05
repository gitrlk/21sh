/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 14:15:48 by jecarol           #+#    #+#             */
/*   Updated: 2016/11/25 17:57:04 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*l;

	i = 0;
	l = (char*)s;
	while (l[i] != c && l[i])
		i++;
	if (l[i] == c)
		return (&l[i]);
	return (NULL);
}
