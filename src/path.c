#include "../minishell.h"

char	**getpaths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			paths = single_split(envp[i] + 5, ':');
			if (paths == NULL)
			{
				ft_putstr_fd("ERROR: paths\n", 1);
				return (NULL);
			}
			break ;
		}
		i++;
	}
	return (paths);
}
