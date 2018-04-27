/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_21_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:46:37 by rfabre            #+#    #+#             */
/*   Updated: 2018/04/27 19:47:29 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int				is_quote_closed(char const *s, char quote)
{
	int			i;

	i = 1;
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote)
		return (1);
	return (0);
}

void			match_d_quotes(t_split *vals, const char *s, char d)
{
	vals->i++;
	while (s[vals->i] != d)
	{
		if (s[vals->i] == '\0')
		{
			vals->cnt--;
			break ;
		}
		vals->i++;
	}
	vals->cnt++;
}

void			match_e_quotes(t_split *vals, const char *s, char e)
{
	vals->i++;
	while (s[vals->i] != e)
	{
		if (s[vals->i] == '\0')
		{
			vals->cnt--;
			break ;
		}
		vals->i++;
	}
	vals->cnt++;
}

void			match_quotes(t_split *vals, const char *s, char d, char e)
{
	if (s[vals->i] == d)
		match_d_quotes(vals, s, d);
	if (s[vals->i] == e)
		match_e_quotes(vals, s, e);
}
