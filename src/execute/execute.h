/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/30 00:43:26 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/21 15:12:57 by ageels        ########   odam.nl         */
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

typedef struct s_doc {
	char			*name;
	int				no;
	int				fd;
	char			*eof;
	struct s_doc	*next;
}	t_doc;

# define READ 0
# define WRITE 1

int			family_life(t_cmd *cmds);
void		child(t_cmd *cmd, int *writep, int *readp, int cmd_no);
pid_t		create_child(t_cmd *cmds, int *wpipe, int *rpipe, int cmd_no);
void		exec_cmd(t_simple *simple, char **envp);
int			only_child(t_cmd *cmds);
void		redirect_infile(t_str_list *infiles);
void		redirect_outfile(t_str_list *outfiles);
int			is_builtin(t_simple	*simple);
int			exec_builtin(t_simple *t, t_cmd *cmd);
t_children	*new_child(pid_t id);
void		child_add_back(t_children *root, t_children *new);
void		free_children(t_children *root);
//void		kill_children(t_children *kids);
t_doc		*docnew(char *eof, int no, t_token *lessless);
void		docadd_back(t_doc **doc, t_doc *new_doc);
char		*heredoc_loop(t_doc *heredoc);

#endif