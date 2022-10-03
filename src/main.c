#include "../minishell.h"

int	cmd_setup(t_cmd *cmd, char **envp)
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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_cmd	cmd;
	char **temp;

	temp = ft_calloc (100000, 19);
	temp[0] = "ls";

	//atexit(run);
	if (cmd_setup(&cmd, envp) == -1)
		return (-1);
	tokens = NULL;
	line = NULL;
	while (1)
	{
		line = prompt();
		catch_signals();
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
			// parse(tokens, &cmd);

			cmd.cmd_count = 1;

// generate_simple_commands doesn't belong here but I dont want to fuck up your parse function :)
			generate_simple_command(&cmd, temp);
			// printf("test99\n");
			if (execute(cmd) == -1)
			{
				dprintf(STDERR_FILENO, "OH NOOOO ~ execute error!\n");
				continue ;
			}
			printf("test98\n");
			//free_token_list(tokens);
			//print_str_list(cmd.infiles, 0);
		}
		free(line);
		line = NULL;
	}
	free(cmd.paths);
	// rl_clear_history();
	return (EXIT_SUCCESS);
}
