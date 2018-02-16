/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 22:26:46 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/04 23:28:21 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char	*trmd;
	int		spaces;
	int		len;
	int		final;

	final = 0;
	spaces = 0;
	if (!s)
		return (NULL);
	len = ft_strlen(s) - 1;
	while (s[spaces] == ' ' || s[spaces] == '\n' || s[spaces] == '\t')
		spaces++;
	if (s[spaces] == '\0')
		return (ft_memalloc(1));
	while (s[len] == ' ' || s[len] == '\n' || s[len] == '\t')
		len--;
	if ((trmd = ft_strnew((len - spaces + 1))) == NULL)
		return (NULL);
	while (spaces <= len)
	{
		trmd[final] = s[spaces];
		final++;
		spaces++;
	}
	return (trmd);
}
