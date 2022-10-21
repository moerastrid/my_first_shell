/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env01.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 21:35:27 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 21:35:51 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	**env_remove(char *var_name, char **envp)
{
	char	*to_remove;
	char	**new_envp;
	int		i;
	int		j;
	int		size;

	to_remove = find_str(var_name, envp);
	if (to_remove == NULL)
		return (envp);
	size = count_envp(envp);
	new_envp = ft_calloc(size, sizeof(envp));
	if (new_envp == NULL)
	{
		g_errno = 12;
		// why not return NULL?
		return (envp);
	}
	i = 0;
	j = 0;
	while (envp && envp[i])
	{
		if (envp[i] != to_remove)
			new_envp[j++] = ft_strdup(envp[i]);
		free(envp[i++]);
	}
	free(envp);
	return (new_envp);
}

void	free_envc(char	**envc)
{
	int	i;

	i = 0;
	while (envc && envc[i])
		free(envc[i++]);
	if (envc)
		free(envc);
}