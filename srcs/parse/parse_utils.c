
#include "../../includes/cub3d.h"

static t_linked_map	*node_map_last(t_linked_map *lst)
{
	if (!lst)
	{
		return (NULL);
	}
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

int	node_map_size(t_linked_map *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
void	node_map_add_back(t_linked_map **lst, t_linked_map *new)
{
	t_linked_map	*last;

	if (!new)
	{
		return ;
	}
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = node_map_last(*lst);
	last->next = new;
}

t_linked_map	*new_node_map(void *content)
{
	t_linked_map	*new_elem;

	new_elem = ft_calloc(1, sizeof(t_linked_map));
	if (!new_elem)
	{
		return (NULL);
	}
	new_elem->line = content;
	return (new_elem);
}
