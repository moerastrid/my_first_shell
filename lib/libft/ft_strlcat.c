/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuyten <tnuyten@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:01:55 by tnuyten           #+#    #+#             */
/*   Updated: 2021/11/02 18:27:32 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char		*d;
	const char	*s;
	size_t		dlen;
	size_t		srclen;

	s = src;
	d = dst;
	srclen = ft_strlen(src);
	while (dstsize != 0 && *d != '\0')
	{
		dstsize--;
		d++;
	}
	dlen = d - dst;
	if (dstsize == 0)
		return (dlen + srclen);
	while (*s != '\0' && dstsize > 1)
	{
		*d = *s++;
		d++;
		dstsize--;
	}
	*d = '\0';
	return (dlen + srclen);
}
