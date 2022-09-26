/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/22 22:20:14 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/26 14:16:30 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define READ 0
# define WRITE 1

//children
int		family_life(int total_cmd, t_list *cmds);
int		parent(int *children, int total_cmd, int *pfd);
int		child(t_list *cmds, int *write_pipe, int *read_pipe, int cmd_no, int total_cmd);

//buildins (00)
void	bi_echo(void);
void	bi_cd(void);
void	bi_pwd(void);
void	bi_export(void);
void	bi_unset(void);
void	bi_env(void);
void	bi_exit(void);

//execute (00)
void	exec_cmd(t_list *cmds, int cmd_no);

#endif
