/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_21.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:47:34 by rfabre            #+#    #+#             */
/*   Updated: 2018/05/03 17:53:58 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

char const		*cut_d_quotes(char const *s, char d, t_split *vals)
{
	if (is_quote_closed(s, d))
	{
		s++;
		vals->t[vals->index] =
		ft_strsub((const char *)s, 0, ft_wlen((const char *)s, d));
		vals->index++;
		s = s + ft_wlen(s, d);
		s++;
	}
	else
	{
		vals->t[vals->index] = ft_strdup("\'");
		vals->index++;
	}
	return (s);
}

char const		*cut_e_quotes(char const *s, char e, t_split *vals)
{
	if (is_quote_closed(s, e))
	{
		s++;
		vals->t[vals->index] =
		ft_strsub((const char *)s, 0, ft_wlen((const char *)s, e));
		vals->index++;
		s = s + ft_wlen(s, e);
		s++;
	}
	else
	{
		vals->t[vals->index] = ft_strdup("\"");
		vals->index++;
	}
	return (s);
}

int				ft_cnt_parts(const char *s, char c, char d, char e)
{
	t_split	vals;

	vals.i = 0;
	vals.in_substring = 0;
	vals.cnt = 0;
	while (vals.i < ((int)ft_strlen(s)))
	{
		match_quotes(&vals, s, d, e);
		if (vals.in_substring == 1 && s[vals.i] == c)
			vals.in_substring = 0;
		if (vals.in_substring == 0 && s[vals.i] != c &&
		s[vals.i] != d && s[vals.i] != e)
		{
			vals.in_substring = 1;
			vals.cnt++;
		}
		vals.i++;
	}
	return (vals.cnt);
}

char			**ft_strsplit_21(char const *s, char c, char d, char e)
{
	t_split	vals;

	if (s == NULL)
		return (NULL);
	vals = init_split(s, c, d, e);
	if (vals.t == NULL)
		return (NULL);
	while (vals.nb_word--)
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s == d)
			s = cut_d_quotes(s, d, &vals);
		else if (*s == e)
			s = cut_e_quotes(s, e, &vals);
		else
		{
			vals.t[vals.index] =
			ft_strsub((const char *)s, 0, ft_wlen((const char *)s, c));
			vals.index++;
			s = s + ft_wlen(s, c);
		}
	}
	return (vals.t);
}
