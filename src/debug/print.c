#include "../../minishell.h"

// Totally illegal
void	print_token_type(enum e_token_type num)
{
	switch (num)
	{
		case 0:
			printf("%s", "WORD");
		break ;
		case 1:
			printf("%s", "GREAT");
		break ;
		case 2:
			printf("%s", "LESS");
		break ;
		case 3:
			printf("%s", "PIPE");
		break ;
		case 4:
			printf("%s", "GREATGREAT");
		break ;
		case 5:
			printf("%s", "LESSLESS");
		break ;
		case 6:
			printf("%s", "DOLL");
		break ;
		case 7:
			printf("%s", "DOLLQ");
		break ;
		case 8:
			printf("%s", "QUOT");
		break ;
		case 9:
			printf("%s", "DQUOT");
		break ;
	}
}

void	print_tokens(t_token *root)
{
	t_token	*i;

	i = root;
	printf("Token list:\t");
	while (i != NULL)
	{
		printf("[");
		print_token_type(i->type);
		printf(", %s]", i->data);
		i = i->next;
		if (i != NULL)
			printf("->");
	}
	printf("\n");
}

void	print_str_list(t_str_list *root, char *name)
{
	if (root != NULL)
		printf("%s: ", name);
	while (root != NULL)
	{
		printf("[%s]", root->str);
		root = root->next;
		if (root != NULL)
			printf("->");
		else
			printf("\n");
	}
}

void	print_simples(t_simple *root)
{
	char		**argv;
	int			i;

	while (root != NULL)
	{
		argv = root->argv;
		printf("Simple {bin:%s\n\t", root->bin);
		i = 0;
		while (i < root->argc)
		{
			printf("[%s]", argv[i++]);
		}
		root = root->next;
		printf("}\n");
	}
}

void print_cmd(t_cmd cmd)
{
	printf("%s\n", "=================================");
	printf("%s\n", "Command struct breakdown:");
	printf("cmd_count: %d\n", cmd.cmd_count);
	print_tokens(cmd.tokens);
	print_simples(cmd.simples);
	print_str_list(cmd.outfiles, "Outfiles");
	print_str_list(cmd.infiles, "Infiles");
	print_str_list(cmd.delimiters, "Delimiters");
	printf("%s: %d\n", "Env size", count_envp(cmd.envc));
	printf("%s\n", "=================================");
}

//void print_children(t_children *root)
//{
//	t_children *ptr;

//	ptr = root;
//	if (ptr == NULL)
//		return ;
//	printf("The kids: [");
//	while(ptr != NULL)
//	{
//		if(ptr->next == NULL)
//			printf("%d]\n", ptr->id);
//		else
//			printf("%d->", ptr->id);
//		ptr = ptr->next;
//	}
//}

void	run_leaks(void)
{
	system("leaks minishell");
}

void	run_lsof(void)
{
	system("lsof -c minishell");
}

void	run_cat_fd(void)
{
	system("cat /dev/fd");
}

// #include <sys/syslimits.h>
# define OPEN_MAX 1000
void	close_all(void)
{
	for(int i = 3; i < OPEN_MAX; i++)
	{
		close(i);
	}
}