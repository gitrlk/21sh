/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freearraystr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 12:49:51 by rfabre            #+#    #+#             */
/*   Updated: 2017/09/03 21:40:06 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freearraystr(char **array)
{
	int	i;

	if (array)
	{
		i = -1;
		while (array[++i])
		{
			ft_strdel(&array[i]);
			free(array[i]);
		}
		free(array);
	}
}
