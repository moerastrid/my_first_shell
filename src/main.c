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
	char	**paths;
	t_cmd	cmd;

	//atexit(run);
	cmd_setup(&cmd);
	paths = getpaths(envp);
	if (!paths)
		return (-1);
	cmd.paths = paths;
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
			parse(tokens, &cmd);
			if (execute(cmd) == -1)
				continue ;
			free_token_list(tokens);
			print_str_list(cmd.infiles, 0);
		}
		free(line);
		line = NULL;
	}
	free(paths);
	// rl_clear_history();
	return (0);
}
