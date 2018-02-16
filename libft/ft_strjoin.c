/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 21:28:15 by rfabre            #+#    #+#             */
/*   Updated: 2017/08/31 17:40:49 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*rslt;
	int		i;
	int		j;
	int		k;

	i = -1;
	if (s1 != NULL && s2 != NULL)
	{
		j = ft_strlen(s1);
		k = ft_strlen(s2);
		if ((rslt = (char*)malloc(sizeof(char) * (j + k + 1))) == NULL)
			return (NULL);
		while (*s1 != '\0')
			rslt[++i] = *s1++;
		while (*s2 != '\0')
			rslt[++i] = *s2++;
		rslt[++i] = '\0';
		return (rslt);
	}
	return (NULL);
}
