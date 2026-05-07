
#include "../../includes/cub3d.h"

static bool	is_in_map_bounds(t_data *data, int y, int x)
{
	if (y < 0 || y >= data->map->map_size)
		return (false);
	if (!data->map->map[y])
		return (false);
	if (x < 0 || x >= (int)ft_strlen(data->map->map[y]))
		return (false);
	return (true);
}

void	change_state_fog_of_war(t_data *data)
{
	int	player_x;
	int	player_y;
	int	dy;
	int	dx;

	player_x = (int)data->raycast->pos_x;
	player_y = (int)data->raycast->pos_y;
	dy = -REVEAL_RADIUS;
	while (dy <= REVEAL_RADIUS)
	{
		dx = -REVEAL_RADIUS;
		while (dx <= REVEAL_RADIUS)
		{
			if (dx * dx + dy * dy <= REVEAL_RADIUS * REVEAL_RADIUS
				&& is_in_map_bounds(data, player_y + dy, player_x + dx))
				data->mini_map.discovered[player_y + dy][player_x + dx] = true;
			dx++;
		}
		dy++;
	}
}