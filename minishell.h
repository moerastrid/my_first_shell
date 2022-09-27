/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ageels <ageels@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/27 22:19:40 by ageels        #+#    #+#                 */
/*   Updated: 2022/09/27 22:25:12 by ageels        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>

# define READ 0
# define WRITE 1

//STRUCTS:
typedef struct s_simple {
	char	**argv;
	char	*bin;
}	t_simple;

typedef struct s_cmd {
	int			amount_cmd;
	t_simple	**simple;
	char		*outfile;
	char		*infile;
	char		*errfile;
}	t_cmd;

typedef struct s_path
{
	char	**paths;
	int		size;
}	t_path;

enum	 e_token_type {
	GREAT = 1,
	LESS = 2,
	PIPE = 3,
	GREATGREAT = 4,
	LESSLESS = 5,
	DOLL = 6,
	DOLLQ = 7,
};

typedef struct s_token {
	enum e_token_type	type;
	char				*data;
	struct s_token		*next;
}	t_token;

// FILES & FUNCTIONS:
//prompt
char	*prompt(void);

//Tokens (00, 01)
t_token	*tokenize(char *input);
t_token	*token_new(char *data, int type);
void	token_add_back(t_token *tokens, t_token *new);

//Parser
int		parse(char *input, t_cmd *cmds, char **envp);

//buildins (00)
void	bi_echo(void);
void	bi_cd(void);
void	bi_pwd(void);
void	bi_export(void);
void	bi_unset(void);
void	bi_env(void);
void	bi_exit(void);

//execute (00, 01)
int		execute(t_cmd cmds);
int		family_life(t_cmd cmds);
int		parent(int *children, t_cmd cmds, int *pfd);
int		child(t_cmd cmds, int *write_pipe, int *read_pipe, int cmd_no);
int		exec_single_cmd(t_cmd cmds);
void	exec_cmd(t_cmd cmds, int cmd_no);

//utils (00)
size_t	ft_strlen(const char *string);
int		ft_putstr_fd(char *s, int fd);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);

//path
t_path	*split_path(char **envp);


#endif
