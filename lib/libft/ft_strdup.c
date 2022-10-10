/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tnuyten <tnuyten@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 14:33:28 by tnuyten       #+#    #+#                 */
/*   Updated: 2022/10/10 21:20:53 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*s2;

	if (!s1)
		len = 0;
	else
		len = ft_strlen(s1);
	s2 = malloc(len + 1);
	if (s2)
		ft_strlcpy(s2, s1, len + 1);
	else
		errno = ENOMEM;
	return (s2);
}
