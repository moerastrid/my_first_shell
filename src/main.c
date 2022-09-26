#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmds;

	char input[50] = "<input.txt cat | wc -l >output.txt";
	parse(input, &cmds);

	//execute();
	//free_structs();

	cmds.amount_cmd = 4;
	family_life(cmds);
}
