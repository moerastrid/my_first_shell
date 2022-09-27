/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils00.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ageels <ageels@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 14:23:22 by ageels            #+#    #+#             */
/*   Updated: 2022/09/27 18:49:08 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *string)
{
	int	a;

	a = 0;
	if (!string)
		return (a);
	while (string[a] != '\0')
		a++;
	return (a);
}

int	ft_putstr_fd(char *s, int fd)
{
	return (write(fd, s, ft_strlen(s)));
}

void	ft_bzero(void *s, size_t n)
{
	char	*stemp;
	size_t	a;

	stemp = (char *)s;
	a = 0;
	while (a != n)
	{
		stemp[a] = '\0';
		a++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*point;

	point = malloc(count * size);
	if (point == NULL)
		return (NULL);
	ft_bzero(point, size * count);
	return (point);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*ptr;

	if (!s)
		return (NULL);
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	while (start-- && *s)
		s++;
	i = 0;
	while (*s && len > 0)
	{
		ptr[i] = *s++;
		len--;
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
