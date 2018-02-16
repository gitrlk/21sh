/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfabre <rfabre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 16:31:19 by rfabre            #+#    #+#             */
/*   Updated: 2016/12/06 21:38:44 by rfabre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	itoa_isnegative(int *n, int *isnegative)
{
	if (*n < 0)
	{
		*n *= -1;
		*isnegative = 1;
	}
}

char		*ft_itoa(int n)
{
	int		temp;
	int		i;
	int		isnegative;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	temp = n;
	i = 2;
	isnegative = 0;
	itoa_isnegative(&n, &isnegative);
	while (temp /= 10)
		i++;
	i += isnegative;
	if ((str = (char*)malloc(sizeof(char) * i)) == NULL)
		return (NULL);
	str[--i] = '\0';
	while (i--)
	{
		str[i] = n % 10 + '0';
		n = n / 10;
	}
	if (isnegative)
		str[0] = '-';
	return (str);
}
