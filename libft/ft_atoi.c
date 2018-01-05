/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 20:17:35 by jecarol           #+#    #+#             */
/*   Updated: 2016/11/25 12:48:02 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\v' || c == '\f' ||
		c == '\r' || c == '\t')
		return (1);
	else
		return (0);
}

int				ft_atoi(const char *str)
{
	int i;
	int neg;
	int nb;

	i = 0;
	neg = 0;
	nb = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	if (str[i] == '-')
		neg = 1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] <= 47 || str[i] >= 58)
		return (0);
	while (str[i] <= 57 && str[i] >= 48 && str[i])
	{
		nb = nb * 10 + str[i] - 48;
		i++;
	}
	if (neg == 1)
		return (-nb);
	return (nb);
}
