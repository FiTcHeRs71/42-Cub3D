
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
	if (data->map->map[y][x] == '1' || data->map->map[y][x] == ' ' || data->map->map[y][x] == 'D')
		return (true);
	return (false);
}

bool is_door_at(t_data *data, double py, double px)
{
	int	y;
	int	x;

	y = (int)py;
	x = (int)px;
	if (y < 0 || y >= data->map->map_size || x < 0)
		return (false);
	if (!data->map->map[y] || x >= (int)ft_strlen(data->map->map[y]))
		return (false);
	if (data->map->map[y][x] == 'd' || data->map->map[y][x] == 'D')
		return (true);
	return (false);
}

void	toggle_nearest_door(t_data *data)
{
	if (!is_door_at(data, data->raycast->dir_y, data->raycast->dir_x))
		return ;
	else
	{
		
	}

}