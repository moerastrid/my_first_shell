#include "../minishell.h"

int	setup(t_cmd *cmd, char **envp)
{
	char	**paths;

	cmd->cmd_count = 0;
	cmd->simples = NULL;
	cmd->outfiles = NULL;
	cmd->infiles = NULL;
	cmd->delimiters = NULL;
	cmd->envp = envp;

	paths = getpaths(envp);
	if (!paths)
		return (-1);
	cmd->paths = paths;
	return (0);
}

void	clear_cmd(t_cmd *cmd)
{
	free_simples(cmd->simples);
	cmd->simples = NULL;
	free_str_list(cmd->outfiles);
	cmd->outfiles = NULL;
	free_str_list(cmd->infiles);
	cmd->infiles = NULL;
	free_str_list(cmd->delimiters);
	cmd->delimiters = NULL;
}

//might be useful
void	freeset(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

static void	reset(t_cmd *cmd, t_children *kids, t_token *tokens)
{
	kill_children(kids);
	free_children(kids);
	g_children = NULL;
	clear_cmd(cmd);
	free_token_list(tokens);
}

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
		//rl_redisplay();
	}
	free(cmd.paths);
	//rl_clear_history();
	return (EXIT_SUCCESS);
}
