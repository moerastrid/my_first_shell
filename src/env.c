#include "../minishell.h"

static int	count_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp && *envp++)
		i++;
	return (i);
}

char	**env_add(char *to_add, char **envp)
{
	int	size;
	char	**new_envp;
	int		i;

	size = count_envp(envp) + 2;
	new_envp = malloc(sizeof(envp) * size);
	i = 0;
	while (envp && envp[i])
	{
		new_envp[i] = ft_strdup(envp[i]);
		free(envp[i]);
		i++;
	}
	new_envp[i++] = ft_strdup(to_add);
	new_envp[i] = NULL;
	free(envp);
	return (new_envp);
}

static char	*find_str(char *str, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], str, ft_strlen(str)) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

char	**env_remove(char *var_name, char **envp)
{
	char	*to_remove;
	char	**new_envp;
	int		i;
	int		j;
	int		size;

	size = count_envp(envp);
	new_envp = malloc(sizeof(envp));
	to_remove = find_str(var_name, envp);
	i = 0;
	j = 0;
	while (envp && envp[i])
	{
		if(envp[i] != to_remove)
			new_envp[j++] = ft_strdup(envp[i]);
		free(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	free(envp);
	return (new_envp);
}
