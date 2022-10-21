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
	print_tokens(cmd->tokens);
	heredoc(cmd);
	substitute(*cmd, cmd->envc);
	if (parse(cmd) != 0)
	{
		printf("%s\n", "parse error");
		reset(cmd, line);
		return ;
	}
	cmd_simples_set_bin(cmd);
	print_tokens(cmd->tokens);
	print_cmd(*cmd);
	g_errno = execute(cmd);
	reset(cmd, line);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;

	// t_token *root = token_new("hi", 1);
	// token_add_back(&root, token_new("bye1", 2));
	// token_add_back(&root, token_new("bye2", 4));
	// token_add_back(&root, token_new("bye3", 8));
	// token_add_back(&root, token_new("bye4", 16));
	// token_add_back(&root, token_new("bye5", 32));
	//
	//
	// print_tokens(root);
	// remove_token_from_list(&root, root);
	// remove_token_from_list(&root, root);
	// remove_token_from_list(&root, root);
	// remove_token_from_list(&root, root);
	// remove_token_from_list(&root, root);
	// remove_token_from_list(&root, root);
	// remove_token_from_list(&root, root);
	// remove_token_from_list(&root, root);
	// remove_token_from_list(&root, root);
	// remove_token_from_list(&root, root);
	// print_tokens(root);
	//
	// return (0);

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
