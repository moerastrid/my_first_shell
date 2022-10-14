#include "../minishell.h"

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
		line = prompt(&cmd);
		if (ft_strlen(line) == 0)
			continue ;
		tokens = tokenize(line);
		if (tokens == NULL)
			continue ;
		substitute(tokens, envp);
		if (parse(tokens, &cmd) != 0)
		{
			reset(&cmd, tokens, line);
			continue ;
		}
		g_errno = execute(&cmd, tokens);
		print_simples(&cmd);
		reset(&cmd, tokens, line);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
