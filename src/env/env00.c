/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env00.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 21:33:09 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 18:01:02 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

char	*find_str(char *str, char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0 \
		&& *(envp[i] + ft_strlen(str)) == '=')
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	**copy_env(char **og)
{
	char	**copy;
	int		i;

	copy = ft_calloc(count_envp(og) + 1, sizeof(char *));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (og[i] != NULL)
	{
		copy[i] = ft_strdup(og[i]);
		i++;
	}
	return (copy);
}

int	count_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp && *envp++)
		i++;
	return (i);
}

int	env_replace(char *var_name, char *insert, char **envp)
{
	int		i;

	i = 0;
	while (envp && envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], var_name, ft_strlen(var_name)) == 0 \
		&& *(envp[i] + ft_strlen(var_name)) == '=')
		{
			free(envp[i]);
			envp[i] = ft_strdup(insert);
			return (0);
		}
		i++;
	}
	return (-1);
}

char	**env_add(char *to_add, char **envp)
{
	char	**new_envp;
	int		i;
	char	*head;

	head = ft_substr(to_add, 0, ft_strchr(to_add, '=') - to_add);
	if (env_replace(head, to_add, envp) == 0)
	{
		free(head);
		return (envp);
	}
	free(head);
	new_envp = ft_calloc(count_envp(envp) + 2, sizeof(envp));
	if (!new_envp)
		return (envp);
	i = 0;
	while (envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	free_envc(envp);
	new_envp[i++] = ft_strdup(to_add);
	return (new_envp);
}
