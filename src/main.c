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
		substitute(cmd.tokens, envp); //What's the order here?
		cmd.paths = getpaths(envp); //What's the order here? Should we get PATH before or after loading the new ENV? export PATH=$PATH/test && echo $PATH Seems to say after, as it uses the new path.
		if (parse(&cmd) != 0)
		{
			printf("%s\n", "parse error");
			reset(&cmd, line);
			continue ;
		}
		cmd_simples_set_bin(&cmd);
		g_errno = execute(&cmd);
		reset(&cmd, line);
	}
	return (EXIT_SUCCESS);
}
