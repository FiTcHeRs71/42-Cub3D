
#include "../../includes/cub3d.h"
#include <math.h>

void	set_dir_vector(t_raycast *ray, t_map *map)
{
	if (map->player_dir == NORTH)
	{
		ray->dir_x = 0;
		ray->dir_y = -1;
	}
	else if (map->player_dir == SOUTH)
	{
		ray->dir_x = 0;
		ray->dir_y = 1;
	}
	else if (map->player_dir == EAST)
	{
		ray->dir_x = 1;
		ray->dir_y = 0;
	}
	else if (map->player_dir == WEST)
	{
		ray->dir_x = -1;
		ray->dir_y = 0;
	}
}

void	set_plane_vector(t_raycast *ray, t_map *map)
{
	if (map->player_dir == NORTH)
	{
		ray->plane_x = 0.66;
		ray->plane_y = 0;
	}
	else if (map->player_dir == SOUTH)
	{
		ray->plane_x = -0.66;
		ray->plane_y = 0;
	}
	else if (map->player_dir == EAST)
	{
		ray->plane_x = 0;
		ray->plane_y = 0.66;
	}
	else if (map->player_dir == WEST)
	{
		ray->plane_x = 0;
		ray->plane_y = -0.66;
	}
}

void	set_data_raycasting(t_raycast *ray, t_map *map)
{
	ray->pos_x = map->player_x + 0.5;
	ray->pos_y = map->player_y + 0.5;
	set_dir_vector(ray, map);
	set_plane_vector(ray, map);
}

void	finalise_DDA_data(t_raycast *ray, t_draw *draw)
{
	if (draw->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (draw->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

void	initialise_DDA(t_raycast *ray, int x, t_data *data, t_draw *draw)
{
	ray->camera_x = 2.0 * x / (double)data->window_x - 1.0;
	draw->raydir_x = ray->dir_x + ray->plane_x * ray->camera_x;
	draw->raydir_y = ray->dir_y + ray->plane_y * ray->camera_x;
	if (draw->raydir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / draw->raydir_x);
	if (draw->raydir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / draw->raydir_y);
}

static bool	is_wall_or_oob(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->map_size)
		return (true);
	if (!map->map[y])
		return (true);
	if (x < 0 || x >= (int)ft_strlen(map->map[y]))
		return (true);
	if (map->map[y][x] == '1' || map->map[y][x] == ' ' || map->map[y][x] == 'D')
		return (true);
	return (false);
}

void	cast_ray(t_data *data, t_raycast *ray, t_draw *draw)
{
	while (!ray->is_hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			draw->wall_side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			draw->wall_side = 1;
		}
		if (is_wall_or_oob(data->map, ray->map_y, ray->map_x))
			ray->is_hit = true;
		if (in_bounds(data, ray->map_y, ray->map_x))
			ray->hit_char = data->map->map[ray->map_y][ray->map_x];
		else
			ray->hit_char = '1';
	}
}

void	set_up_drawing_data(t_data *data, t_raycast *ray, t_draw *draw)
{
	draw->line_h = (int)(data->window_y / ray->wall_dist);
	draw->line_start = -draw->line_h / 2 + data->window_y / 2;
	if (draw->line_start < 0)
		draw->line_start = 0;
	draw->line_end = draw->line_h / 2 + data->window_y / 2;
	if (draw->line_end >= data->window_y)
		draw->line_end = data->window_y - 1;
}

void	*raycasting(void *arg)
{
	t_thread_data	*td;
	t_raycast		ray;
	t_draw			draw;

	td = (t_thread_data *)arg;
	ft_memset(&ray, 0, sizeof(t_raycast));
	ft_memset(&draw, 0, sizeof(t_draw));
	ray.pos_x = td->data->raycast->pos_x;
	ray.pos_y = td->data->raycast->pos_y;
	ray.dir_x = td->data->raycast->dir_x;
	ray.dir_y = td->data->raycast->dir_y;
	ray.plane_x = td->data->raycast->plane_x;
	ray.plane_y = td->data->raycast->plane_y;
	draw_background(td, &ray);
	while (td->x_start < td->x_end)
	{
		initialise_DDA(&ray, td->x_start, td->data, &draw);
		ray.map_x = (int)ray.pos_x;
		ray.map_y = (int)ray.pos_y;
		finalise_DDA_data(&ray, &draw);
		cast_ray(td->data, &ray, &draw);
		if (draw.wall_side == 0)
			ray.wall_dist = (ray.side_dist_x - ray.delta_dist_x);
		else
			ray.wall_dist = (ray.side_dist_y - ray.delta_dist_y);
		set_up_drawing_data(td->data, &ray, &draw);
		draw_wall(td->data, &ray, &draw, td->x_start);
		ray.is_hit = false;
		td->x_start++;
	}
	return (NULL);
}
