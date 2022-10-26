/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 19:19:31 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	bi_cd(t_simple *simple, t_cmd *cmd)
{
	char	*str;
	char	*retstr;

	if (simple->argc == 1)
		str = find_str("HOME", cmd->envc) + 5;
	else
		str = simple->argv[1];
	if ((int)str == 5)
		return (1);
	if (chdir(str) != 0)
	{
		perror(str);
		return (1);
	}
	else
	{
		retstr = getcwd(NULL, 0);
		if (retstr == NULL)
			return (1);
		retstr = ft_strjoin_free(ft_strdup("PWD="), retstr);
		cmd->envc = env_add(retstr, cmd->envc);
		free(retstr);
	}
	return (0);
}
