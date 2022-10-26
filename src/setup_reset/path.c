/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 16:37:30 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 19:15:35 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "setup.h"

char	**getpaths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			paths = single_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (paths);
}
