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
			continue ;
		cmd.tokens = tokenize(line);
		if (cmd.tokens == NULL)
			continue ;
		// print_tokens(cmd.tokens);
		substitute(cmd.tokens, envp); //What's the order here?
		cmd.paths = getpaths(envp); //What's the order here?
		// print_tokens(cmd.tokens);
		if (parse(&cmd) != 0)
		{
			reset(&cmd, line);
			continue ;
		}
		// print_cmd(cmd);
		g_errno = execute(&cmd);
		// print_cmd(cmd);
		reset(&cmd, line);
	}
	rl_clear_history();
	return (EXIT_SUCCESS);
}
