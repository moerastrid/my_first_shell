/* ************************************************************************** */
/*                                                                            */
<<<<<<< HEAD
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ageels <ageels@student.codam.nl>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:20:02 by ageels            #+#    #+#             */
/*   Updated: 2022/09/26 14:12:20 by tnuyten          ###   ########.fr       */
=======
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:20:02 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/26 14:02:16 by ageels        ########   odam.nl         */
>>>>>>> 711df93e536ae2e7d6ffc7d1566a3cdf9877d433
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	parse(argc, argv);
	execute();
	free_structs();
}
