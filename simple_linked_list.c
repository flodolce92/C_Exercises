#include <stdio.h>
#include <stdlib.h>

typedef struct s_item
{
	int				num;
	struct s_item	*next_item;
}	t_item;

int	main(int ac, char **av)
{
	t_item	*item_list;
	int		num_item;
	int		i;

	if (ac < 2 || ac - 2 != atoi(av[1]))
	{
		printf("EH NO!\n");
		return (1);
	}
	num_item = atoi(av[1]);

	item_list = (t_item *) malloc(sizeof(t_item) * num_item);
	if (!item_list)
		printf("Memory fault.\n");
	else
		printf("Allocated %d elements:\n", num_item);
	
	i = 0;
	while (i < num_item)
	{
		item_list[i].num = atoi(av[2 + i]);
		if (i + 1 != num_item)
			item_list[i].next_item = &item_list[i + 1];
		else
			item_list[i].next_item = NULL;
		i++;
	}

	i = 0;
	while (i < num_item)
	{
		printf("Item n. %d: %d | link: %p\n", i + 1, item_list[i].num, item_list[i].next_item);
		i++;
	}
	return (0);
}
