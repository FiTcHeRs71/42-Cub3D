/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 12/05/2026 10:27:10 by fducrot           #+#    #+#             */
/*   Updated: 18/05/2026 10:50:28 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	is_wall_or_oob(t_map *map, int y, int x)
{
	if (y < 0 || y >= map->map_size)
		return (true);
	if (!map->map[y])
		return (true);
	if (x < 0 || x >= map->line_len[y])
		return (true);
	if (map->map[y][x] == '1' || map->map[y][x] == ' ' || map->map[y][x] == 'D')
		return (true);
	return (false);
}

static void	cast_ray(t_data *data, t_raycast *ray, t_draw *draw)
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

static void	set_up_drawing_data(t_data *data, t_raycast *ray, t_draw *draw)
{
	draw->line_h = (int)(data->window_y / ray->wall_dist);
	draw->line_start = -draw->line_h / 2 + data->window_y / 2;
	if (draw->line_start < 0)
		draw->line_start = 0;
	draw->line_end = draw->line_h / 2 + data->window_y / 2;
	if (draw->line_end >= data->window_y)
		draw->line_end = data->window_y - 1;
}

static void	prep_raycast(t_thread_data *td, t_raycast *ray)
{
	ft_memset(ray, 0, sizeof(t_raycast));
	ray->pos_x = td->data->raycast->pos_x;
	ray->pos_y = td->data->raycast->pos_y;
	ray->dir_x = td->data->raycast->dir_x;
	ray->dir_y = td->data->raycast->dir_y;
	ray->plane_x = td->data->raycast->plane_x;
	ray->plane_y = td->data->raycast->plane_y;
	draw_background(td, ray);
}

void	*raycasting(void *arg)
{
	t_thread_data	*td;
	t_raycast		ray;
	t_draw			draw;

	td = (t_thread_data *)arg;
	ft_memset(&draw, 0, sizeof(t_draw));
	prep_raycast(td, &ray);
	while (td->x_start < td->x_end)
	{
		init_dda(&ray, td->x_start, td->data, &draw);
		ray.map_x = (int)ray.pos_x;
		ray.map_y = (int)ray.pos_y;
		finalise_dda_data(&ray, &draw);
		cast_ray(td->data, &ray, &draw);
		if (draw.wall_side == 0)
			ray.wall_dist = (ray.side_dist_x - ray.delta_dist_x);
		else
			ray.wall_dist = (ray.side_dist_y - ray.delta_dist_y);
		td->data->z_buffer[td->x_start] = ray.wall_dist;
		set_up_drawing_data(td->data, &ray, &draw);
		draw_wall(td->data, &ray, &draw, td->x_start);
		ray.is_hit = false;
		td->x_start++;
	}
	return (NULL);
}
