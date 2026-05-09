
#include "../../includes/cub3d.h"

t_enemy	*new_enemy(double x, double y)
{
	t_enemy	*node;

	node = ft_calloc(1, sizeof(t_enemy));
	if (!node)
		return (NULL);
	node->pos_x = x;
	node->pos_y = y;
	node->dist = 0.0;
	node->next = NULL;
	return (node);
}

static t_enemy	*enemy_last(t_enemy *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	enemy_add_back(t_enemy **lst, t_enemy *new_one)
{
	t_enemy	*last;

	if (!new_one)
		return ;
	if (!*lst)
	{
		*lst = new_one;
		return ;
	}
	last = enemy_last(*lst);
	last->next = new_one;
}

void	free_enemies(t_enemy *enemies)
{
	t_enemy	*tmp;

	while (enemies)
	{
		tmp = enemies;
		enemies = enemies->next;
		free(tmp);
	}
}