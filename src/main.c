#include "../minishell.h"

void	minishell(t_cmd *cmd)
{
	char	*line;

	line = prompt(cmd);
	if (ft_strlen(line) == 0)
	{
		free(line);
		return ;
	}
	if (tokenize(cmd, line) == -1 || cmd->tokens == NULL)
	{
		reset(cmd, line);
		return ;
	}
		//heredoc?
	substitute(*cmd, cmd->envc);
	if (parse(cmd) != 0)
	{
		printf("%s\n", "parse error");
		reset(cmd, line);
		return ;
	}
	cmd_simples_set_bin(cmd);
	print_cmd(*cmd);
	g_errno = execute(cmd);
	reset(cmd, line);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;

	(void)argv;
	if (setup(&cmd, envp, argc) == -1)
		return (-1);
	while (1)
	{
		minishell(&cmd);
	}
	return (EXIT_SUCCESS);
}

//ls | cat >out.txt <in.txt >>out2.txt | echo -e -r -m $SHLVL=a/b
