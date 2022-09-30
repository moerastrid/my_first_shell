#include "../minishell.h"

char	*prompt(void)
{
	char	*line;

	line = readline(" (⁠╯⁠°⁠□⁠°⁠）⁠╯⁠︵⁠ ⁠┻⁠━⁠┻ ");
	if (!line)
		return (NULL);
	if (*line)
		add_history(line);
	return (line);
}
