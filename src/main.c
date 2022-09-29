/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 16:54:53 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/29 21:15:25 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_setup(t_cmd *cmd)
{
	cmd->cmd_count = 0;
	cmd->simples = NULL;
	cmd->outfiles = NULL;
	cmd->infiles = NULL;
	cmd->delimiters = NULL;
}

// Totally illegal
static void	print_token_type(enum e_token_type num)
{
	switch (num)
	{
		case 0:
			printf("%s", "WORD");
		break ;
		case 1:
			printf("%s", "GREAT");
		break ;
		case 2:
			printf("%s", "LESS");
		break ;
		case 3:
			printf("%s", "PIPE");
		break ;
		case 4:
			printf("%s", "GREATGREAT");
		break ;
		case 5:
			printf("%s", "LESSLESS");
		break ;
		case 6:
			printf("%s", "DOLL");
		break ;
		case 7:
			printf("%s", "DOLLQ");
		break ;
	}
}

static void	print_tokens(t_token *root)
{
	t_token	*i;

	i = root;
	printf("Token list:\n");
	while (i != NULL)
	{
		printf("[");
		print_token_type(i->type);
		printf(", %s]", i->data);
		i = i->next;
		if (i != NULL)
			printf("->");
	}
	printf("\n");
}

static void	run(void)
{
	system("leaks minishell");
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*tokens;
	t_path	*paths;
	t_cmd	cmd;

	//atexit(run);
	cmd_setup(&cmd);
	paths = split_path(envp);
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
			parse(tokens, &cmd, paths);
			if (execute(cmd) == -1)
			{
				continue ;
			}
			free_token_list(tokens);
		}
		free(line);
		line = NULL;
	}
	free_paths(paths);
	// rl_clear_history();
	return (0);
}
