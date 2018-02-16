/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 19:22:10 by rfabre            #+#    #+#             */
/*   Updated: 2016/12/06 20:45:05 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*temp;

	if (s != NULL && (*f) != NULL)
	{
		if ((temp = (char*)malloc(sizeof(char) * (ft_strlen(s) + 1))) == NULL)
			return (NULL);
		i = -1;
		while (s[++i])
		{
			temp[i] = f(s[i]);
		}
		temp[i] = '\0';
		return (temp);
	}
	return (NULL);
}
