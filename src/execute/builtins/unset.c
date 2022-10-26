/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 14:02:35 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 19:18:54 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	ft_exit_err(char *str, int err)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	return (err);
}

static int	is_valid_env_var(char *name)
{
	char	*ptr;

	ptr = name;
	if (!(ft_isalpha(*ptr) || *ptr == '_'))
		return (ft_exit_err(name, 0));
	while ((ft_isalpha(*ptr) || *ptr == '_' || \
	ft_isdigit(*ptr)) && *ptr != '\0')
		ptr++;
	if (*ptr == '\0')
		return (1);
	return (0);
}

int	bi_unset(t_simple simple, t_cmd *cmd)
{
	int		i;
	int		val;
	int		ret;

	i = 1;
	ret = 0;
	while (simple.argv[i])
	{
		val = is_valid_env_var(simple.argv[i]);
		if (val)
			cmd->envc = env_remove(simple.argv[i], cmd->envc);
		else
			ret = 1;
		i++;
	}
	return (ret);
}
