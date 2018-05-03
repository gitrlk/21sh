/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_more.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 18:48:49 by jecarol           #+#    #+#             */
/*   Updated: 2018/05/03 15:14:14 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

void			go_down(t_edit *line)
{
	if ((line->cursor_pos % ((line->sz.ws_col)) == 0))
	{
		tputs(tgetstr("do", NULL), 1, ft_pointchar);
		tputs(tgetstr("cr", NULL), 1, ft_pointchar);
	}
}

void			double_ignore(char *s, t_parsing *data)
{
	int			match;
	int			start;

	match = 0;
	if (s[data->index] == '\"')
	{
		start = data->index;
		data->index++;
		while (s[data->index])
		{
			if (s[data->index] == '\"')
			{
				match = 1;
				break ;
			}
			data->index++;
		}
		if (match == 0)
			data->index = start;
	}
}

void			simple_ignore(char *s, t_parsing *data)
{
	int			match;
	int			start;

	match = 0;
	if (s[data->index] == '\'')
	{
		start = data->index;
		data->index++;
		while (s[data->index])
		{
			if (s[data->index] == '\'')
			{
				match = 1;
				break ;
			}
			data->index++;
		}
		if (match == 0)
			data->index = start;
	}
}

void			ignore_quotes(char *s, t_parsing *data, int mod)
{
	if (mod == 1)
	{
		simple_ignore(s, data);
		double_ignore(s, data);
	}
	if (mod == 2)
		ignore_quotes_more(s, data);
}
