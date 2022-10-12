#ifndef PARSER_H
# define PARSER_H

# include "../../minishell.h"

// Parser.c
int			parse(t_token *tokens, t_cmd *cmd);

// cmd_builder.c
void		add_outfile(t_cmd *cmd, int append_mode, char *data);
void		add_infile(t_cmd *cmd, char *data);
void		add_delimiter(t_cmd *cmd, char *data);
int			add_arg(t_simple *simple, char *arg);

// simple.c
void		free_simples(t_simple *simples);
void		simple_add_back(t_simple **lst, t_simple *new_elem);
t_simple	*new_simple(int argc, char **argv);

// str_list.c
t_str_list	*str_list_new(char *str, int append_mode);
void		str_list_add_back(t_str_list *root, t_str_list *new);
void		free_str_list(t_str_list *root);

#endif