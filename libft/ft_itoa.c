/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecarol <jecarol@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 12:24:32 by jecarol           #+#    #+#             */
/*   Updated: 2016/12/07 15:08:12 by jecarol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_how_long(int n)
{
	int		i;

	i = 0;
	while (n /= 10)
		i++;
	return (i);
}

char				*ft_itoa(int n)
{
	char	*cnvrt;
	int		len;
	int		is_neg;

	is_neg = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		is_neg = 1;
		n = -n;
	}
	len = ft_how_long(n) + is_neg + 2;
	if ((cnvrt = (char*)malloc(sizeof(char) * len)) == NULL)
		return (NULL);
	cnvrt[--len] = '\0';
	while (len--)
	{
		cnvrt[len] = n % 10 + 48;
		n = n / 10;
	}
	if (is_neg == 1)
		cnvrt[0] = '-';
	return (cnvrt);
}
