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

static void print_simples(t_cmd *cmd)
{
	t_simple	*simple;
	char		**argv;
	int			i;

	simple = cmd->simples;
	while(simple != NULL)
	{
		argv = simple->argv;
		printf("Simple {bin:%s, argv:[", simple->bin);
		i = 0;
		while(i < simple->argc)
		{
			if(i + 1 == simple->argc)
				printf("%s", argv[i++]);
			else
				printf("%s, ", argv[i++]);
		}
		simple = simple->next;
		printf("]}\n");
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_cmd	cmd;
	char **temp;
	g_children = ft_calloc(1000, 1000);

	temp = ft_calloc (100000, 19);
	temp[0] = "ls";

	//atexit(run);
	if (cmd_setup(&cmd, envp) == -1)
		return (-1);
	tokens = NULL;
	line = NULL;
	while (1)
	{
		catch_signals();
		line = prompt();
		if (!line)
			continue ;
		if (*line)
		{
			tokens = tokenize(line);
			if (tokens == NULL)
				continue ;
			print_tokens(tokens);
			parse(tokens, &cmd);
			print_simples(&cmd);

			if (execute(cmd) == -1)
			{
				dprintf(STDERR_FILENO, "OH NOOOO ~ execute error!\n");
				continue ;
			}
			free_token_list(tokens);
			//print_str_list(cmd.infiles, 0);
		}
		free(line);
		line = NULL;
	}
	free(cmd.paths);
	// rl_clear_history();
	return (EXIT_SUCCESS);
}
