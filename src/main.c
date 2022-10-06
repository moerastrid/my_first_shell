#include "../minishell.h"

int	setup(t_cmd *cmd, char **envp)
{
	char	**paths;

	cmd->cmd_count = 0;
	cmd->simples = NULL;
	cmd->outfiles = NULL;
	cmd->infiles = NULL;
	cmd->delimiters = NULL;

	paths = getpaths(envp);
	if (!paths)
		return (-1);
	cmd->paths = paths;
	return (0);
}

static void	run(void)
{
	system("leaks minishell");
}

static void	clear_cmd(t_cmd *cmd)
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

void	kill_children(t_children *kids)
{
	while(kids != NULL)
	{
		printf("%d\n", kids->id);
		kill(kids->id, SIGKILL);
		kids = kids->next;
	}
}

static void reset(t_cmd *cmd, t_children *kids, t_token *tokens)
{
	free_token_list(tokens);
	clear_cmd(cmd);
	free_children(g_children);
	g_children = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_cmd	cmd;

	// atexit(run);
	if (setup(&cmd, envp) == -1)
		return (-1);
	line = NULL;
	catch_signals();
	while (1)
	{
		line = prompt();
		tokens = tokenize(line);
		if (tokens == NULL)
			continue ;
		parse(tokens, &cmd);
		if (execute(cmd) == -1)
			dprintf(STDERR_FILENO, "OH NOOOO ~ execute error!\n");
		print_tokens(tokens);
		print_simples(&cmd);
		print_children(g_children);
		kill_children(g_children);
		reset(&cmd, g_children, tokens);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		free(line);
		//rl_redisplay();
	}
	free(cmd.paths);
	//rl_clear_history();
	return (EXIT_SUCCESS);
}
