/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 15:43:18 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/26 19:00:45 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../minishell.h"

// Parser.c


// cmd_builder.c
int			cmd_add_pipe(t_cmd *cmd);

// parce_redirects.c
int			parse_redirect(t_cmd *cmd, t_token **token);
int			parse_heredoc(t_cmd *cmd, t_token **token);

// set_bin.c
void		cmd_simples_set_bin(t_cmd *cmd);

// simple_argv_builder.c
int			simple_add_outfile(t_simple *simple, char *data, int append_mode);
int			simple_add_infile(t_simple *simple, char *data, int append_mode);
int			add_arg(t_cmd *cmd, char *arg);

// simple_free.c
void		free_simples(t_simple *simples);

// simple.c
void		simple_add_back(t_simple **lst, t_simple *new_elem);
t_simple	*new_simple(int argc, char **argv);
t_simple	*simple_tail(t_simple *simple);
int			count_simples(t_cmd *cmd);

// str_list.c
t_str_list	*str_list_new(char *str, int append_mode);
void		str_list_add_back(t_str_list *root, t_str_list *new);
void		free_str_list(t_str_list *root);

#endif