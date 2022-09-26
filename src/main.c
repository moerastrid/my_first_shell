/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ageels <ageels@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:54:53 by ageels            #+#    #+#             */
/*   Updated: 2022/09/26 20:53:25 by tnuyten          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	if (prompt() != 0)
	{
		ft_putstr_fd("no prompt today", 1);
		return (1);
	}
	//execute();
	//free_structs();

	// cmds.amount_cmd = 4;
	//family_life(cmds);
}
