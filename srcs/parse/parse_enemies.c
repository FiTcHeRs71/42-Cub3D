
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

void	add_enemy(t_data *data, int i, int y, char *line)
{
	enemy_add_back(&data->enemies, new_enemy((double)i + 0.5, (double)y
			+ 0.5));
	if (!data->enemies)
		ft_error(ERR_MALLOC, data);
	data->enemy_count++;
	line[i] = '0';
}

void	init_pos_player(t_data *data, char *line, int i, int y)
{
	if (ft_strchr("N", line[i]))
		data->map->player_dir = NORTH;
	if (ft_strchr("S", line[i]))
		data->map->player_dir = SOUTH;
	if (ft_strchr("W", line[i]))
		data->map->player_dir = WEST;
	if (ft_strchr("E", line[i]))
		data->map->player_dir = EAST;
	data->map->player_x = i;
	data->map->player_y = y;
	data->map->player_flag += 1;
}
