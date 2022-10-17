#ifndef DEBUG_H
# define DEBUG_H

# include "../../minishell.h"

//DEBUG #TODO REMOVE... ILLEGAL FUNCTION!
void		print_token_type(enum e_token_type num);
void		print_str_list(t_str_list *root, char *name);
void		print_tokens(t_token *root);
void		print_simples(t_simple *root);
void		print_envc(char **envc);
void		run_leaks(void);
void		run_lsof(void);
void		run_cat_fd(void);
void		close_all(void);
void		print_cmd(t_cmd cmd);

#endif