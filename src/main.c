#include "../minishell.h"

int	setup(t_cmd *cmd, char **envp)
{
	char	**paths;

	cmd->cmd_count = 0;
	cmd->simples = NULL;
	cmd->outfiles = NULL;
	cmd->infiles = NULL;
	cmd->delimiters = NULL;
	g_children.id = -1;
	g_children.next = NULL;

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

static void	free_simple(t_simple *simple)
{
	int	i;

	i = 0;
	while (i < simple->argc)
		free(simple->argv[i++]);
	free(simple->argv);
	free(simple->bin);
	simple->argv = NULL;
	simple->bin = NULL;
}

static void	free_simples(t_simple *simples)
{
	t_simple	*next;

	while (simples != NULL)
	{
		free_simple(simples);
		next = simples->next;
		free(simples);
		simples = next;
	}
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

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_cmd	cmd;

	//atexit(run);
	if (setup(&cmd, envp) == -1)
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
			//print_tokens(tokens);
			parse(tokens, &cmd);
			//print_simples(&cmd);
			if (execute(cmd) == -1)
			{
				dprintf(STDERR_FILENO, "OH NOOOO ~ execute error!\n");
				//continue;
			}
			ft_putstr_fd("\n", STDERR_FILENO);
			rl_on_new_line();
			free_token_list(tokens);
			clear_cmd(&cmd);
		}
		free(line);
		rl_on_new_line();
	}
	free(cmd.paths);
	//rl_clear_history();
	return (EXIT_SUCCESS);
}
