#include "../includes/sh.h"

void 	cut_d_quotes(char const *s, char d, t_split *vals)
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
		vals->t[vals->index] = ft_strdup(&d);
		vals->index++;
	}
}

void 	cut_e_quotes(char const *s, char e, t_split *vals)
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
		vals->t[vals->index] = ft_strdup(&e);
		vals->index++;
	}
}

int		ft_cnt_parts(const char *s, char c, char d, char e)
{
	t_split 	vals;

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
	t_split 	vals;

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
			cut_d_quotes(s, d, &vals);
		else if (*s == e)
			cut_e_quotes(s, e, &vals);
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
