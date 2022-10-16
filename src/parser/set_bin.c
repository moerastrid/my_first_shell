#include "parser.h"

void	set_bin(t_cmd *cmd, t_simple *simple)
{
	char	*myexec;
	int		i;

	if (!simple || !simple->argv || !cmd)
		return ;
	if (ft_strchr(simple->argv[0], '/') != NULL || access(simple->argv[0], X_OK) == 0)
	{
		simple->bin = ft_strdup(simple->argv[0]);
		if (access(simple->bin, X_OK) == -1)
			errno = 2;
		return ;
	}
	i = 0;
	while (cmd->paths && cmd->paths[i])
	{
		myexec = ft_strjoin3(cmd->paths[i++], "/", simple->argv[0]);
		if (!myexec)
			return ;
		if (access(myexec, X_OK) == 0)
		{
			errno = 0;
			simple->bin = myexec;
			return ;
		}
		free (myexec);
	}
	return ;
}