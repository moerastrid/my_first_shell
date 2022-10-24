/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/24 22:18:39 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	bi_cd(t_simple *simple, t_cmd *cmd)
{
	char	*str;
	char	*retstr;
	char	*retstr2;

	print_simples(cmd->simples);
	if (simple->argc == 1)
		str = find_str("HOME", cmd->envc) + 5;
	else
		str = simple->argv[1];
	printf("string: %s\n", str);
	if ((int)str == 5)
		return (1);
	if (chdir(str) != 0)
		perror(str);
	else
	{
		retstr = getcwd(NULL, 0);
		retstr2 = ft_strjoin("PWD=", retstr);
		cmd->envc = env_add(retstr2, cmd->envc);
		free (retstr2);
		free(retstr);
	}
	return (0);
}
