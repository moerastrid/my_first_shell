#include "../minishell.h"

char	*prompt(void)
{
	char	*line;

	line = readline(" (⁠╯⁠°⁠□⁠°⁠）⁠╯⁠︵⁠ ⁠┻⁠━⁠┻ ");
	if (line == NULL)
	{
		ft_putstr_fd("exit on line = NULL\n", STDERR_FILENO);
		exit(0);
	}
	if (*line)
		add_history(line);
	return (line);
}
