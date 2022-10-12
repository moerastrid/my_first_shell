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
	catch_signals();
	while (1)
	{
		// system("ls /dev/fd");
		line = prompt();
		drop_signals();
		tokens = tokenize(line);
		if (tokens == NULL)
			continue ;
		print_tokens(tokens);
		substitute(tokens, envp);
		print_tokens(tokens);
		if(parse(tokens, &cmd) == -1)
		{
			free_token_list(tokens);
			continue;
		}
		// print_tokens(tokens);
		print_simples(&cmd);
		// print_children(g_children);
		if (execute(cmd, tokens) == -1)
			dprintf(STDERR_FILENO, "OH NOOOO ~ execute error!\n");

		reset(&cmd, g_children, tokens);
		rl_on_new_line();
		free(line);
		catch_signals();
	}
	free(cmd.paths);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
