/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tnuyten <tnuyten@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/26 13:20:57 by tnuyten       #+#    #+#                 */
/*   Updated: 2022/09/26 14:18:13 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void parse(int argc, char **argv)
{
	check_fds();
	setup_cmd_lst();
	replace_def_arg();
}
