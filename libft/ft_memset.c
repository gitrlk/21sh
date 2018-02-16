/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 16:36:00 by rfabre            #+#    #+#             */
/*   Updated: 2017/06/17 17:16:46 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t		i;
	char		*ch_b;

	ch_b = (char*)b;
	i = 0;
	while (i < len)
	{
		ch_b[i] = (char)c;
		i++;
	}
	return (b);
}
