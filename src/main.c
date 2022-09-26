#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	parse(argc, argv);
	execute();
	free_structs();
}
