/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnuyten <tnuyten@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:09:22 by tnuyten           #+#    #+#             */
/*   Updated: 2022/09/29 17:22:01 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putendl_fd(char *s, int fd)
{
	int	written;
	int	temp;

	temp = 0;
	written = 0;
	if (!s)
		return (0);
	written = ft_putstr_fd(s, fd);
	if (written == -1)
		return (-1);
	temp = write(fd, "\n", 1);
	if (temp == -1)
		return (-1);
	return (written + temp);
}
