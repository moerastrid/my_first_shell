#include "../minishell.h"

void	minishell(t_cmd *cmd, char **input)
{
	char	*line;
	char	*retstr;

	retstr = NULL;
	if (*input == NULL)
	{

		printf("%s\n", "prompting");
		line = prompt(cmd);
	}
	else
		line = ft_strdup(*input);
	if (ft_strlen(line) == 0)
	{
		*input = NULL;
		free(line);
		return ;
	}
	ft_putstr_fd(line, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (tokenize(cmd, line) == -1 || cmd->tokens == NULL)
	{
		*input = NULL;
		reset(cmd, line);
		return ;
	}
	print_tokens(cmd->tokens);
	int err = heredoc(cmd, &retstr);
	if (err)
	{
		*input = NULL;
		reset(cmd, line);
		return ;
	}
	if (retstr != NULL)
	{
		*input = NULL;
		reset(cmd, line);
		*input = retstr;
		return ;
	}
	substitute(*cmd, cmd->envc);
	if (parse(cmd) != 0)
	{
		printf("%s\n", "parse error");
		*input = NULL;
		reset(cmd, line);
		return ;
	}
	cmd_simples_set_bin(cmd);
	print_tokens(cmd->tokens);
	print_cmd(*cmd);
	g_errno = execute(cmd);
	reset(cmd, line);
	*input = NULL;
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;

	char *input = NULL;
	(void)argv;
	if (setup(&cmd, envp, argc) == -1)
		return (-1);
	while (1)
	{
		minishell(&cmd, &input);
	}
	return (EXIT_SUCCESS);
}

//ls | cat >out.txt <in.txt >>out2.txt | echo -e -r -m $SHLVL=a/b
