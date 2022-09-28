/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuyten <tnuyten@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 21:44:53 by tnuyten           #+#    #+#             */
/*   Updated: 2021/10/28 17:16:55 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_length(int n)
{
	int	res;

	res = 0;
	if (n == 0)
		res++;
	if (n < 0)
	{
		n = -n;
		res++;
	}
	while (n > 0)
	{
		n /= 10;
		res++;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*res;

	if (n == -2147483648)
	{
		return (ft_strdup("-2147483648"));
	}
	i = n_length(n);
	res = malloc(i + 1);
	if (!res)
		return (NULL);
	res[i] = '\0';
	res[0] = '0';
	if (n < 0)
	{
		n = -n;
		res[0] = '-';
	}
	while (n > 0)
	{
		--i;
		res[i] = n % 10 + '0';
		n /= 10;
	}
	return (res);
}
