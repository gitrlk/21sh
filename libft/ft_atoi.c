/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:15:07 by rfabre            #+#    #+#             */
/*   Updated: 2016/12/05 18:29:38 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int i;
	int result;
	int sign;

	i = 0;
	result = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (ft_isdigit(str[i + 1]))
		{
			sign = (str[i] == '+') ? 1 : -1;
			i++;
		}
		else
			return (0);
	}
	while (ft_isdigit(str[i]))
		result = result * 10 + str[i++] - '0';
	result *= sign;
	return (result);
}
