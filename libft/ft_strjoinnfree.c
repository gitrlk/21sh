/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinnfree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 15:01:19 by rfabre            #+#    #+#             */
/*   Updated: 2018/02/06 15:01:29 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoinnfree(char *s1, char *s2, size_t len, char b12)
{
	char	*s;
	char	*ret;
	char	*tmp1;
	char	*tmp2;

	s = ft_strnew(ft_strlen(s1) + len + 1);
	ret = s;
	tmp1 = s1;
	tmp2 = s2;
	while (*s1)
		*s++ = *s1++;
	while (*s2 && len--)
		*s++ = *s2++;
	if (b12 == '1' || b12 == 'b')
		free(tmp1);
	if (b12 == '2' || b12 == 'b')
		free(tmp2);
	return (ret);
}
