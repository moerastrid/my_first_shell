/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_builder.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/21 22:29:12 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/24 22:28:18 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	cmd_add_pipe(t_cmd *cmd)
{
	t_simple	*new;

	new = new_simple(0, NULL);
	if (simple_tail(cmd->simples)->argv == NULL)
	{
		g_errno = 258;
		printf("syntax error near unexpected token '|'\n");
		return (-1);
	}
	simple_add_back(&cmd->simples, new);
	return (0);
}
