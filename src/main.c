#include "../minishell.h"

void	cmd_setup(t_cmd *cmd)
{
	cmd->cmd_count = 0;
	cmd->simples = NULL;
	cmd->outfiles = NULL;
	cmd->infiles = NULL;
	cmd->delimiters = NULL;
}

static void	run(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_path	*paths;
	t_cmd	cmd;

	//atexit(run);
	cmd_setup(&cmd);
	paths = split_path(envp);
	tokens = NULL;
	line = NULL;
	while (1)
	{
		line = prompt();
		if (!line)
			continue ;
		if (*line)
		{
			tokens = tokenize(line);
			if (tokens == NULL)
			{
				printf("%s\n", NULL);
				continue ;
			}
			print_tokens(tokens);
			parse(tokens, &cmd, paths);
			if (execute(cmd) == -1)
			{
				continue ;
			}
			free_token_list(tokens);
		}
		free(line);
		line = NULL;
	}
	free_paths(paths);
	// rl_clear_history();
	return (0);
}
