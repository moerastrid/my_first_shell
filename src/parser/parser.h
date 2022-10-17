/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 15:43:18 by ageels        #+#    #+#                 */
/*   Updated: 2022/10/17 16:55:51 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../minishell.h"

// Parser.c
//int			parse(t_token *tokens, t_cmd *cmd);

// cmd_builder.c
int			add_outfile(t_cmd *cmd, int append_mode, char *data);
int			add_infile(t_cmd *cmd, int append_mode, char *data);
//int			add_delimiter(t_cmd *cmd, char *data);
int			add_arg(t_cmd *cmd, char *arg);
int			add_pipe(t_cmd *cmd);

// simple.c
//void		free_simples(t_simple *simples);
void		simple_add_back(t_simple **lst, t_simple *new_elem);
t_simple	*new_simple(int argc, char **argv);
t_simple	*simple_tail(t_simple *simple);

// str_list.c
t_str_list	*str_list_new(char *str, int append_mode);
void		str_list_add_back(t_str_list *root, t_str_list *new);
//void		free_str_list(t_str_list *root);

//set_bin.c
void		set_bin(t_cmd *cmd, t_simple *simple);

#endif