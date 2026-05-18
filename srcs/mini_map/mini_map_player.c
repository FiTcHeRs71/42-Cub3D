/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 10:49:30 by fducrot           #+#    #+#             */
/*   Updated: 2026/05/18 10:49:30 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <sys/param.h>

static void	bresenham_step(int p[5], int *x0, int *y0)
{
	int	e2;

	e2 = 2 * p[4];
	if (e2 >= p[1])
	{
		p[4] += p[1];
		*x0 += p[2];
	}
	if (e2 <= p[0])
	{
		p[4] += p[0];
		*y0 += p[3];
	}
}

static void	draw_line(t_data *data, int start[2], int end[2])
{
	int	p[5];
	int	x0;
	int	y0;

	x0 = start[0];
	y0 = start[1];
	p[0] = abs(end[0] - x0);
	p[1] = -abs(end[1] - y0);
	if (x0 < end[0])
		p[2] = 1;
	else
		p[2] = -1;
	if (y0 < end[1])
		p[3] = 1;
	else
		p[3] = -1;
	p[4] = p[0] + p[1];
	while (1)
	{
		mm_put_pixel(data, x0, y0, MM_COLOR_CONE);
		if (x0 == end[0] && y0 == end[1])
			break ;
		bresenham_step(p, &x0, &y0);
	}
}

void	draw_mini_map_cone(t_data *data)
{
	int		start[2];
	int		end[2];
	double	len;

	len = data->mini_map.scale * MM_CONE_LENGTH;
	start[0] = data->mini_map.pos_x + (int)(data->raycast->pos_x
			* data->mini_map.scale);
	start[1] = data->mini_map.pos_y + (int)(data->raycast->pos_y
			* data->mini_map.scale);
	end[0] = start[0] + (int)((data->raycast->dir_x
				+ data->raycast->plane_x) * len);
	end[1] = start[1] + (int)((data->raycast->dir_y
				+ data->raycast->plane_y) * len);
	draw_line(data, start, end);
	end[0] = start[0] + (int)((data->raycast->dir_x
				- data->raycast->plane_x) * len);
	end[1] = start[1] + (int)((data->raycast->dir_y
				- data->raycast->plane_y) * len);
	draw_line(data, start, end);
}

void	compute_minimap_fullscreen(t_data *data)
{
	int	scale_x;
	int	scale_y;

	scale_x = data->window_x / data->largest_line;
	scale_y = data->window_y / data->map->map_size;
	if (scale_x < scale_y)
		data->mini_map.scale = scale_x;
	else
		data->mini_map.scale = scale_y;
	data->mini_map.width = data->mini_map.scale * data->largest_line;
	data->mini_map.height = data->mini_map.scale * data->map->map_size;
	data->mini_map.pos_x = (data->window_x - data->mini_map.width) / 2;
	data->mini_map.pos_y = (data->window_y - data->mini_map.height) / 2;
}

void	toggle_minimap_fullscreen(t_data *data)
{
	data->mini_map.fullscreen = !data->mini_map.fullscreen;
	if (data->mini_map.fullscreen)
		compute_minimap_fullscreen(data);
	else
		compute_minimap_normal(data);
}
