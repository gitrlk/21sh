/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 19:17:52 by jecarol           #+#    #+#             */
/*   Updated: 2016/12/07 16:33:25 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_words(const char *s, char c)
{
	unsigned int	i;
	int				compteur;

	i = 0;
	compteur = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			compteur++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (compteur);
}

char			**ft_split1(char const *s, char c, char **str)
{
	int			i;
	int			j;
	int			k;
	int			l;

	i = 0;
	k = 0;
	while (s[i])
	{
		l = 0;
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
		{
			str[k] = (char *)malloc(sizeof(char) * (i - j + 1));
			while (j < i)
				str[k][l++] = s[j++];
			str[k++][l] = '\0';
		}
	}
	str[k] = NULL;
	return (str);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**str;

	if (!s)
		return (NULL);
	if ((str = (char **)malloc(sizeof(char*) * ft_words(s, c) + 1)) == NULL)
		return (NULL);
	return (ft_split1(s, c, str));
}
