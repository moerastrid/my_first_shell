#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	parse(argc, argv);
	//execute();
	//free_structs();
	t_cmd	cmds;
	cmds.amount_cmd = 4;
	family_life(cmds);
}
