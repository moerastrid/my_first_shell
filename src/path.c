#include "../minishell.h"

void free_paths(t_path *paths)
{
	int i = 0;

	while (paths->paths != NULL)
	{
		free(paths->paths[i++]);
	}
	free(paths->paths);
	free(paths);
}

// return envp[i]+5 to cut off "PATH="
static char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

t_path	*split_path(char **envp)
{
	char	*path;
	t_path	*paths;
	int		path_size;

	path = find_path(envp);
	if (path == NULL)
		return (NULL);
	paths = malloc(sizeof(t_path));
	if (paths == NULL)
		return (NULL);
	paths->paths = ft_split(path, ':');
	if (paths->paths == NULL)
	{
		free(paths);
		return (NULL);
	}
	path_size = 0;
	while (paths->paths[path_size] != NULL)
		path_size++;
	paths->size = path_size;
	return (paths);
}
