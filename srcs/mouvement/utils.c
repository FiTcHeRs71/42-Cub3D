
#include "../../includes/cub3d.h"
#include <limits.h>

bool	is_wall_at(t_data *data, double px, double py)
{
	int	x;
	int	y;

	x = (int)px;
	y = (int)py;
	if (y < 0 || x < 0 || y >= data->map->map_size)
		return (true);
	if (!data->map->map[y] || x >= (int)ft_strlen(data->map->map[y]))
		return (true);
	if (data->map->map[y][x] == '1' || data->map->map[y][x] == ' '
		|| data->map->map[y][x] == 'D')
		return (true);
	return (false);
}

bool	in_bounds(t_data *data, int y, int x)
{
	if (y < 0 || y >= data->map->map_size)
		return (false);
	if (!data->map->map[y])
		return (false);
	if (x < 0 || x >= (int)ft_strlen(data->map->map[y]))
		return (false);
	return (true);
}

static void	check_one_case(t_data *data, int dy, int dx, int *best, int out[2])
{
	int		player_x;
	int		player_y;
	int		case_x;
	int		case_y;
	char	c;

	player_x = (int)data->raycast->pos_x;
	player_y = (int)data->raycast->pos_y;
	case_x = player_x + dx;
	case_y = player_y + dy;
	if (!in_bounds(data, case_y, case_x))
		return ;
	c = data->map->map[case_y][case_x];
	if (c != 'D' && c != 'd')
		return ;
	if (dx * dx + dy * dy < *best)
	{
		*best = dx * dx + dy * dy;
		out[0] = case_x;
		out[1] = case_y;
	}
}

bool	find_nearest_door(t_data *data, int *out_x, int *out_y)
{
	int	dx;
	int	dy;
	int	best;
	int	out[2];

	best = 999;
	out[0] = -1;
	out[1] = -1;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (!(dx == 0 && dy == 0))
				check_one_case(data, dy, dx, &best, out);
			dx++;
		}
		dy++;
	}
	if (out[0] == -1)
		return (false);
	*out_x = out[0];
	*out_y = out[1];
	return (true);
}

void	toggle_nearest_door(t_data *data)
{
	int	x;
	int	y;

	if (!find_nearest_door(data, &x, &y))
		return ;
	if (data->map->map[y][x] == 'D')
		data->map->map[y][x] = 'd';
	else
	{
		if ((int)data->raycast->pos_x == x && (int)data->raycast->pos_y == y)
			return ;
		data->map->map[y][x] = 'D';
	}
}
