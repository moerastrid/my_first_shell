/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 00:43:26 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/14 14:43:09 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../../minishell.h"
# include "./builtins/builtins.h"

typedef struct s_children {
	pid_t				id;
	struct s_children	*next;
}	t_children;

# define READ 0
# define WRITE 1

int			family_life(t_cmd cmds);
void		child(t_cmd cmd, int *writep, int *readp, int cmd_no);
pid_t		create_child(t_cmd cmds, int *wpipe, int *rpipe, int cmd_no);
void		exec_cmd(t_simple *simple, char **envp);
int			only_child(t_cmd cmds);
void		redirect_infile(t_str_list *infiles);
void		redirect_outfile(t_str_list *outfiles);
int			is_builtin(t_simple	*simple);
int			exec_builtin(t_simple *t, t_cmd cmd, t_token *tokens);
t_children	*new_child(pid_t id);
void		child_add_back(t_children *root, t_children *new);
//void		free_children(t_children *root);
//void		kill_children(t_children *kids);

#endif