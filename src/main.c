#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	cmd;

	(void)argv;
	if (setup(&cmd, envp, argc) == -1)
		return (-1);
	line = NULL;
	while (1)
	{
		line = prompt(&cmd);
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		if(tokenize(&cmd, line) == -1 || cmd.tokens == NULL)
		{
			reset(&cmd, line);
			continue;
		}
		substitute(cmd.tokens, envp); //What's the order here?
		cmd.paths = getpaths(envp); //What's the order here?
		if (parse(&cmd) != 0)
		{
			reset(&cmd, line);
			continue ;
		}
		print_cmd(cmd);
		g_errno = execute(&cmd);
		reset(&cmd, line);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
