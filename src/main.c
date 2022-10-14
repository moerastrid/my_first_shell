#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_cmd	cmd;

	// atexit(run_leaks);
	if (setup(&cmd, envp) == -1)
		return (-1);
	line = NULL;
	while (1)
	{
		cmd.paths = getpaths(envp);
		line = prompt();
		tokens = tokenize(line);
		if (tokens == NULL)
		{
			printf("%s\n", "token error");
			continue ;
		}
		print_tokens(tokens);
		substitute(tokens, envp);
		//print_tokens(tokens);
		if(parse(tokens, &cmd) == -1)
		{
			free_token_list(tokens);
			dprintf(STDERR_FILENO, "OH NOOOO ~ parse error!\n");
			continue ;
		}
		print_tokens(tokens);
		print_simples(&cmd);
		// print_children(g_children);
		g_errno = execute(cmd, tokens);
		reset(&cmd, g_children, tokens);
		free(line);
		rl_on_new_line();
	}
	// free env (still have to write this function)
	rl_clear_history();
	return (EXIT_SUCCESS);
}
