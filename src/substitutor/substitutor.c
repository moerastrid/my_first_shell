#include "../../minishell.h"

void substitute(t_cmd *cmd)
{
	t_simple	*simple;
	char		**envp;
	char		**argv;

	envp = cmd->envp;
	simple = cmd->simples;

	// while(simple)
	// {
	// 	argv = simple->argv;
	// 	while(argv)
	// 	{
	// 		argv++;
	// 	}
	// 	simple = simple->next;
	// }
}
