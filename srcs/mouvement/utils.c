
#include "../../includes/cub3d.h"

bool is_wall_at(t_data *data, double px, double py)
{
	int x;
	int y;

	x = (int)px;
	y = (int)py;
	if (y < 0 || x < 0 || y >= data->map->map_size)
		return (true);
	if (!data->map->map[y] || x >= (int)ft_strlen(data->map->map[y]))
		return (true);
	if (data->map->map[y][x] == '1' || data->map->map[y][x] == ' ')
		return (true);
	return (false);
}