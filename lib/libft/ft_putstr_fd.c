/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuyten <tnuyten@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:09:22 by tnuyten           #+#    #+#             */
/*   Updated: 2022/09/29 17:19:51 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	written;
	int	temp;

	temp = 0;
	written = 0;
	if (!s)
		return (written);
	while (*s)
	{
		temp = ft_putchar_fd(*s++, fd);
		if (temp == -1)
			return (-1);
		written += temp;
	}
	return (written);
}
