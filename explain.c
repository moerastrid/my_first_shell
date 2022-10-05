
typedef struct s_node
{
	int				id;
	struct s_node	*next;
} node;

node *node_new(int id)
{
	node *new;

	new = malloc(sizeof(node));
	if (new == NULL)
		return (NULL);
	new->id = id;
	new->next = NULL;
	return (new);
}

void node_add_back_single_ptr(node *root, node *new)
{
	node *ptr;

	if (root == NULL)
		return ;
	ptr = root;
	while(ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new;
}

void node_add_back_double_ptr(node **root, node *new)
{
	if(root == NULL)
		root = new;
}

int main(int argc, char const *argv[])
{

	return 0;
}