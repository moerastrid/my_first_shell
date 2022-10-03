#include "../minishell.h"

char	*prompt(void)
{
	char	*line;

	line = readline(" (⁠╯⁠°⁠□⁠°⁠）⁠╯⁠︵⁠ ⁠┻⁠━⁠┻ ");
	if (!line)
		exit(0);
	if (*line)
		add_history(line);
	return (line);
}
