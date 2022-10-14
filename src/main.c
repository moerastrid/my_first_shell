#include "../minishell.h"

void	free_envc(char	**envc)
{
	int	i;

	i = 0;
	while (envc && envc[i])
	{
		free(envc[i]);
		i++;
	}
	free(envc);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_cmd	cmd;

	if (setup(&cmd, envp, argc) == -1)
		return (-1);
	line = NULL;
	while (1)
	{
		cmd.paths = getpaths(envp);
		line = prompt();
		if (ft_strlen(line) == 0)
			continue ;
		tokens = tokenize(line);
		if (tokens == NULL)
			continue ;
		substitute(tokens, envp);
		if(parse(tokens, &cmd) == -1)
		{
			free_token_list(tokens);
			continue ;
		}
		g_errno = execute(cmd, tokens);
		reset(&cmd, g_children, tokens);
		free(line);
		rl_on_new_line();
	}
	free_envc(cmd.envc);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
