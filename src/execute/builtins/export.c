/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/12 14:12:13 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 19:19:17 by ageels        ########   odam.nl         */
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

static int	is_valid_env_line(char *name)
{
	char	*ptr;

	ptr = name;
	if (!(ft_isalpha(*ptr) || *ptr == '_'))
		return (ft_exit_err(name, 0));
	while ((ft_isalpha(*ptr) || *ptr == '_' || \
	ft_isdigit(*ptr)) && *ptr != '\0')
		ptr++;
	if (*ptr == '\0')
		return (2);
	if (*ptr != '=')
		return (ft_exit_err(name, 0));
	return (1);
}

static void	export_print_env(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->envc[i] != NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		j = 0;
		while (cmd->envc[i][j] != '\0')
		{
			ft_putchar_fd(cmd->envc[i][j], STDOUT_FILENO);
			if (cmd->envc[i][j] == '=')
				ft_putchar_fd('\"', STDOUT_FILENO);
			j++;
		}
		ft_putstr_fd("\"\n", STDOUT_FILENO);
		i++;
	}
}

int	bi_export(t_simple simple, t_cmd *cmd)
{
	int		i;
	int		ret;
	int		val;
	char	**env;

	ret = 0;
	if (simple.argc == 1)
		export_print_env(cmd);
	i = 1;
	while (simple.argv[i])
	{
		val = is_valid_env_line(simple.argv[i]);
		if (val == 1)
		{
			env = env_add(simple.argv[i], cmd->envc);
			cmd->envc = env;
		}
		else if (val == 0)
			ret = 1;
		i++;
	}
	return (ret);
}
