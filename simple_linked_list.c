#include <stdio.h>
#include <stdlib.h>

typedef struct s_item
{
	int				num;
	struct s_item	*next_item;
}	t_item;

t_item	*create_item(void)
{
	t_item	*temp;

	temp = (t_item *) malloc(sizeof(t_item));
	temp->next_item = NULL;
	return (temp);
}

t_item	*add_item(t_item *head, int val)
{
	t_item	*temp;
	t_item	*p;

	temp = create_item();
	temp->num = val;
	if (head == NULL)
		head = temp;
	else
	{
		p = head;
		while (p->next_item != NULL)
			p = p->next_item;
		p->next_item = temp;
	}
	return (head);
}

int	main(int ac, char **av)
{
	t_item	*head;
	t_item	*p;
	int		i;

	if (ac < 2 || ac - 2 != atoi(av[1]))
	{
		printf("Args error.\n");
		return (1);
	}
	head = NULL;
	i = 2;
	while (av[i])
	{
		head = add_item(head, atoi(av[i]));
		i++;
	}
	p = head;
	while (p != NULL)
	{
		printf("Data %d at %p\n", p->num, p);
		p = p->next_item;
	}
	return (0);
}
