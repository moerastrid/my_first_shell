#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_cmd	cmd;

	(void)argv;
	if (setup(&cmd, envp, argc) == -1)
		return (-1);
	line = NULL;
	while (1)
	{
		line = prompt(&cmd);
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		if (tokenize(&cmd, line) == -1 || cmd.tokens == NULL)
		{
			reset(&cmd, line);
			continue ;
		}
		cmd.paths = getpaths(envp);
		substitute(cmd, envp);
		if (parse(&cmd) != 0)
		{
			printf("%s\n", "parse error");
			reset(&cmd, line);
			continue ;
		}
		cmd_simples_set_bin(&cmd);
		print_cmd(cmd);
		g_errno = execute(&cmd);
		reset(&cmd, line);
	}
	return (EXIT_SUCCESS);
}

//ls | cat >out.txt <in.txt >>out2.txt | echo -e -r -m $SHLVL=a/b
