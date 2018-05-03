/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_misc_more.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 01:50:33 by jecarol           #+#    #+#             */
/*   Updated: 2018/05/03 03:56:09 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int		return_free(char *tmp, char *tmp1)
{
	ft_strdel(&tmp);
	ft_strdel(&tmp1);
	return (0);
}

void	ignore_more_double(char *s, t_parsing *data)
{
	int	match;
	int	start;

	match = 0;
	if (s[data->subber] == '\"')
	{
		start = data->subber;
		data->subber++;
		while (s[data->subber])
		{
			if (s[data->subber] == '\"')
			{
				match = 1;
				break ;
			}
			data->subber++;
		}
		if (match == 0)
			data->subber = start;
	}
}

void	ignore_more_simple(char *s, t_parsing *data)
{
	int	match;
	int	start;

	match = 0;
	if (s[data->subber] == '\'')
	{
		start = data->subber;
		data->subber++;
		while (s[data->subber])
		{
			if (s[data->subber] == '\'')
			{
				match = 1;
				break ;
			}
			data->subber++;
		}
		if (match == 0)
			data->subber = start;
	}
}

void	ignore_quotes_more(char *s, t_parsing *data)
{
	ignore_more_simple(s, data);
	ignore_more_double(s, data);
}
