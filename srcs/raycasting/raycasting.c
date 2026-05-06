
#include "../../includes/cub3d.h"
#include <math.h>

void	set_dir_vector(t_raycast *data, t_map *map)
{
	if (map->payer_dir == NORTH)
	{
		data->dir_x = 0;
		data->dir_y = -1;
	}
	else if (map->payer_dir == SOUTH)
	{
		data->dir_x = 0;
		data->dir_y = 1;
	}
	else if (map->payer_dir == EAST)
	{
		data->dir_x = 1;
		data->dir_y = 0;
	}
	else if (map->payer_dir == WEST)
	{
		data->dir_x = -1;
		data->dir_y = 0;
	}
}

void	set_plane_vector(t_raycast *data, t_map *map)
{
	if (map->payer_dir == NORTH)
	{
		data->plane_x = 0.66;
		data->plane_y = 0;
	}
	else if (map->payer_dir == SOUTH)
	{
		data->plane_x = -0.66;
		data->plane_y = 0;
	}
	else if (map->payer_dir == EAST)
	{
		data->plane_x = 0;
		data->plane_y = 0.66;
	}
	else if (map->payer_dir == WEST)
	{
		data->plane_x = 0;
		data->plane_y = -0.66;
	}
}

void	set_data_raycasting(t_raycast *data, t_map *map)
{
	data->pos_x = map->player_x;
	data->pos_y = map->player_y;
	set_dir_vector(data, map);
	set_plane_vector(data, map);
}

void	finalise_DDA_data(t_raycast *data)
{
	if (data->ray_dir_x < 0)
	{
		data->step_x = -1;
		data->side_dist_x = (data->pos_x - data->map_x) * data->delta_dist_x;
	}
	else
	{
		data->step_x = 1;
		data->side_dist_x = (data->map_x + 1.0 - data->pos_x) * data->delta_dist_x;
	}
	if (data->ray_dir_y < 0)
	{
		data->step_y = -1;
		data->side_dist_y = (data->pos_y - data->map_y) * data->delta_dist_y;
	}
	else
	{
		data->step_y = 1;
		data->side_dist_y = (data->map_y + 1.0 - data->pos_y) * data->delta_dist_y;
	}
}

void	initialise_DDA(t_raycast *data, int x, t_data *stats)
{
	data->camera_x = 2.0 * x / (double)stats->window_x - 1;
	data->ray_dir_x = data->dir_x + data->plane_x * data->camera_x;
	data->ray_dir_y = data->dir_y + data->plane_y * data->camera_x;
	if (data->ray_dir_x == 0)
		data->delta_dist_x = 1e30;
	else
		data->delta_dist_x = fabs(1 / data->ray_dir_x);
	if (data->ray_dir_y == 0)
		data->delta_dist_y = 1e30;
	else
		data->delta_dist_y = fabs(1 / data->ray_dir_y);
}

void	cast_ray(t_data *stats, t_raycast *data)
{
	while (!data->is_hit)
	{
		if (data->side_dist_x < data->side_dist_y)
		{
			data->side_dist_x += data->delta_dist_x;
			data->map_x += data->step_x;
			data->wall_side = 0;
		}
		else
		{
			data->side_dist_y += data->delta_dist_y;
			data->map_y += data->step_y;
			data->wall_side = 1;
		}
		if (stats->map->map[data->map_y][data->map_x] > '0')
			data->is_hit = true;
	}
}

void	set_up_drawing_data(t_data *stats, t_raycast *data, t_draw *draw)
{
	draw->line_h = (int)(stats->window_y / data->wall_dist);
	draw->line_start = -draw->line_h / 2 + stats->window_y / 2;
	if (draw->line_start < 0)
		draw->line_start = 0;
	draw->line_end = draw->line_h / 2 + stats->window_y / 2;
	if (draw->line_end >= stats->window_y)
		draw->line_end = stats->window_y - 1;
}

void	raycasting(t_data *stats, t_raycast *data, t_draw *draw)
{
	int	x;

	x = 0;
	while (x < stats->window_x)
	{
		initialise_DDA(data, x, stats);
		data->map_x = (int)data->pos_x;
		data->map_y = (int)data->pos_y;
		finalise_DDA_data(data);
		cast_ray(stats, data);
		if (data->wall_side == 0)
			data->wall_dist = (data->side_dist_x - data->delta_dist_x);
		else
			data->wall_dist = (data->side_dist_y - data->delta_dist_y);
		set_up_drawing_data(stats, data, draw);
		draw_wall(stats, data, draw, x);
		data->is_hit = false;
		x++;
	}
}



// si on va vers le nord, dirY diminue, vers le sud il augmente (x ne change pas)
// si on va vers l'ouest il diminue, vers l'est dirX augmente (y ne change pas)