/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freejoinstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:48:05 by rfabre            #+#    #+#             */
/*   Updated: 2018/01/07 18:50:32 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_freejoinstr(char *dst, char *src)
{
	char	*tmp;

	if (!(tmp = malloc(sizeof(char) * (ft_strlen(dst) + 1))))
		return (NULL);
	tmp[0] = '\0';
	ft_strcpy(tmp, dst);
	ft_strdel(&dst);
	if ((dst = ft_strjoin(tmp, src)) == NULL)
		return (NULL);
	ft_strdel(&tmp);
	return (dst);
}
