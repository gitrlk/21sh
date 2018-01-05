/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 15:38:48 by jecarol           #+#    #+#             */
/*   Updated: 2016/12/02 18:37:12 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s)
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
		return (ft_strnew(0));
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
