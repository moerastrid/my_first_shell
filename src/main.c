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

static void free_simple(t_simple *simple)
{
	int	i;

	i = 0;
	while(i < simple->argc)
	{
		free(simple->argv[i++]);
	}
	free(simple->argv);
	free(simple->bin);
	simple->argv = NULL;
	simple->bin = NULL;
}

static void free_simples(t_simple *simples)
{
	t_simple	*next;

	while(simples != NULL)
	{
		free_simple(simples);
		next = simples->next;
		free(simples);
		simples = next;
	}
}

static void clear_cmd(t_cmd *cmd)
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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_cmd	cmd;
	char **temp;


	g_children = ft_calloc(OPEN_MAX, sizeof(pid_t));

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
				continue ;
			print_tokens(tokens);
			parse(tokens, &cmd);
			print_simples(&cmd);

			if (execute(cmd) == -1)
			{
				dprintf(STDERR_FILENO, "OH NOOOO ~ execute error!\n");
			}
			free_token_list(tokens);
			clear_cmd(&cmd);
		}
		free(line);
		line = NULL;
	}
	free(cmd.paths);
	// rl_clear_history();
	return (EXIT_SUCCESS);
}
