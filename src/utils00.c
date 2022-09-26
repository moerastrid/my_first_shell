/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils00.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 14:23:22 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/26 14:24:15 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	if (point == 0)
		return (0);
	ft_bzero(point, size * count);
	return (point);
}
