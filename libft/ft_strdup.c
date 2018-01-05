/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 19:46:50 by jecarol           #+#    #+#             */
/*   Updated: 2016/11/25 13:03:15 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*char	*ft_strdup(const char *s1)
  {
  int		i;
  char	*s2;

  i = 0;
  s2 = (char*)malloc(sizeof(*s2) * (ft_strlen(s1) + 1));
  if (s2 == NULL)
  return (NULL);
  while (s1[i])
  {
  s2[i] = s1[i];
  i++;
  }
  s2[i] = '\0';
  return (s2);
  }*/

char	*ft_strdup(const char *s1)
{
	char *result;
	int i;
	int j;

	i = 0;
	if (!(result = (char*)malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	j = (ft_strlen(s1));
	while (j >= 0)
	{
		result[i] = s1[i];
		i++;
		j--;
	}
	return (result);
}
