
#include "../../includes/cub3d.h"
#include <math.h>

void	set_dir_vector(t_raycast *data, t_map *map)
{
	if (map->player_dir == NORTH)
	{
		data->dir_x = 0;
		data->dir_y = -1;
	}
	else if (map->player_dir == SOUTH)
	{
		data->dir_x = 0;
		data->dir_y = 1;
	}
	else if (map->player_dir == EAST)
	{
		data->dir_x = 1;
		data->dir_y = 0;
	}
	else if (map->player_dir == WEST)
	{
		data->dir_x = -1;
		data->dir_y = 0;
	}
}

void	set_plane_vector(t_raycast *data, t_map *map)
{
	if (map->player_dir == NORTH)
	{
		data->plane_x = 0.66;
		data->plane_y = 0;
	}
	else if (map->player_dir == SOUTH)
	{
		data->plane_x = -0.66;
		data->plane_y = 0;
	}
	else if (map->player_dir == EAST)
	{
		data->plane_x = 0;
		data->plane_y = 0.66;
	}
	else if (map->player_dir == WEST)
	{
		data->plane_x = 0;
		data->plane_y = -0.66;
	}
}

void	set_data_raycasting(t_raycast *data, t_map *map)
{
	data->pos_x = map->player_x + 0.5;
	data->pos_y = map->player_y + 0.5;
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
	data->camera_x = 2.0 * x / (double)stats->window_x - 1.0;
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

static bool	is_wall_or_oob(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->map_size)
		return (true);
	if (!map->map[y])
		return (true);
	if (x < 0 || x >= (int)ft_strlen(map->map[y]))
		return (true);
	if (map->map[y][x] == '1' || map->map[y][x] == ' ')
		return (true);
	return (false);
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
		if (is_wall_or_oob(stats->map, data->map_y, data->map_x))
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

void	*raycasting(void *arg)
{
	t_thread_data	*td;
	t_raycast		ray;
	t_draw			draw;

	td = (t_thread_data *)arg;
	ft_memset(&ray, 0, sizeof(t_raycast));
	ft_memset(&draw, 0, sizeof(t_draw));
	ray.pos_x = td->stats->raycast->pos_x;
	ray.pos_y = td->stats->raycast->pos_y;
	ray.dir_x = td->stats->raycast->dir_x;
	ray.dir_y = td->stats->raycast->dir_y;
	ray.plane_x = td->stats->raycast->plane_x;
	ray.plane_y = td->stats->raycast->plane_y;
	while (td->x_start < td->x_end)
	{
		initialise_DDA(&ray, td->x_start, td->stats);
		ray.map_x = (int)ray.pos_x;
		ray.map_y = (int)ray.pos_y;
		finalise_DDA_data(&ray);
		cast_ray(td->stats, &ray);
		if (ray.wall_side == 0)
			ray.wall_dist = (ray.side_dist_x - ray.delta_dist_x);
		else
			ray.wall_dist = (ray.side_dist_y - ray.delta_dist_y);
		set_up_drawing_data(td->stats, &ray, &draw);
		draw_wall(td->stats, &ray, &draw, td->x_start);
		draw_floor(td->stats, &ray, &draw, td->x_start);
		draw_ceiling(td->stats, &ray, &draw, td->x_start);
		ray.is_hit = false;
		td->x_start++;
	}
	return (NULL);
}
