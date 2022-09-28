/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuyten <tnuyten@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 13:45:25 by tnuyten           #+#    #+#             */
/*   Updated: 2021/10/26 21:32:16 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*d;

	if (dst == NULL && src == NULL && n != 0)
		return (NULL);
	d = dst;
	while (n)
	{
		*((unsigned char *)dst) = *((unsigned char *)src);
		dst++;
		src++;
		n--;
	}
	return (d);
}
