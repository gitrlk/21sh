/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_misc_more.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 01:50:33 by jecarol           #+#    #+#             */
/*   Updated: 2018/05/03 01:50:34 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/sh.h"

int				return_free(char *tmp, char *tmp1)
{
	ft_strdel(&tmp);
	ft_strdel(&tmp1);
	return (0);
}

void			ignore_quotes_more(char *s, t_parsing *data)
{
	if (s[data->subber] == '\'')
	{
		data->subber++;
		while (s[data->subber] != '\'')
			data->subber++;
	}
	if (s[data->subber] == '\"')
	{
		data->subber++;
		while (s[data->subber] != '\"')
			data->subber++;
	}
}
