/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tnuyten <tnuyten@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/11 13:13:15 by tnuyten       #+#    #+#                 */
/*   Updated: 2021/10/13 20:36:09 by tnuyten       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	f_res;
	int		len;
	char	*res;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		f_res = (*f)(i, s[i]);
		res[i] = f_res;
		i++;
	}
	res[i] = '\0';
	return (res);
}
