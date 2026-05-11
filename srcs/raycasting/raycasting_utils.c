#include "../../includes/cub3d.h"

static void	set_dir_vector(t_raycast *ray, t_map *map)
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

static void	set_plane_vector(t_raycast *ray, t_map *map)
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

void	finalise_dda_data(t_raycast *ray, t_draw *draw)
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

void	init_dda(t_raycast *ray, int x, t_data *data, t_draw *draw)
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
