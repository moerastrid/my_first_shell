#include "substitutor.h"
#include "../heredoc/heredoc.h"

char	*substitute_line(char *line, char **envp)
{
	char	*ptr;
	int		pre_sub_len;
	char	*new_line;

	ptr = line;
	while (ptr && *ptr != '\0')
	{
		while (*ptr != '$' && *ptr != '\0')
			ptr++;
		if (*ptr == '\0')
			break ;
		new_line = replace_once(ptr, line, &pre_sub_len, envp);
		free(line);
		line = new_line;
		ptr = line + pre_sub_len;
	}
	return (line);
}
