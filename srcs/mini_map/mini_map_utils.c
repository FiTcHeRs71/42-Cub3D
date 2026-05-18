/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/05/2026 10:47:57 by fducrot           #+#    #+#             */
/*   Updated: 11/05/2026 10:47:57 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	mm_put_pixel(t_data *data, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x < 0 || x >= data->window_x || y < 0 || y >= data->window_y)
		return ;
	offset = (y * data->mlx->size_line) + (x * (data->mlx->bits_per_pixel / 8));
	pixel = data->mlx->img_data + offset;
	*(unsigned int *)pixel = color;
}

int	choose_color_mini_map_cells(char grid)
{
	if (grid == 'd')
		return (MM_COLOR_DOOR_OPEN);
	else if (grid == 'D')
		return (MM_COLOR_DOOR_CLOSED);
	else if (grid == '1')
		return (MM_COLOR_WALL);
	return (MM_COLOR_FLOOR);
}

void	compute_minimap_normal(t_data *data)
{
	data->mini_map.width = data->window_x * MINIMAP_RATIO;
	data->mini_map.height = data->window_y * MINIMAP_RATIO;
	data->mini_map.scale = data->mini_map.width / data->largest_line;
	data->mini_map.pos_x = data->window_x - data->mini_map.width - 10;
	data->mini_map.pos_y = 10;
}

void	draw_mini_map_player(t_data *data)
{
	int	pixel_x;
	int	pixel_y;
	int	dx;
	int	dy;
	int	size;

	size = 5;
	pixel_x = data->mini_map.pos_x + (int)(data->raycast->pos_x
			* data->mini_map.scale);
	pixel_y = data->mini_map.pos_y + (int)(data->raycast->pos_y
			* data->mini_map.scale);
	dy = -size / 2;
	while (dy <= size / 2)
	{
		dx = -size / 2;
		while (dx <= size / 2)
		{
			mm_put_pixel(data, pixel_x + dx, pixel_y + dy, MM_COLOR_PLAYER);
			dx++;
		}
		dy++;
	}
}
