/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinmulti.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 18:31:43 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/03 16:13:09 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoinmulti(char const *s1, char const *s2, char const *s3)
{
	char	*s;
	int		i;
	int		j;
	int		k;

	if (s1 != NULL && s2 != NULL && s3 != NULL)
	{
		j = ft_strlen(s1);
		k = ft_strlen(s2);
		i = ft_strlen(s3);
		if ((s = (char*)malloc(sizeof(char) * (j + k + i + 1))) == NULL)
			return (NULL);
		i = -1;
		while (*s1 != '\0')
			s[++i] = *s1++;
		while (*s2 != '\0')
			s[++i] = *s2++;
		while (*s3 != '\0')
			s[++i] = *s3++;
		s[++i] = '\0';
		return (s);
	}
	return (NULL);
}
