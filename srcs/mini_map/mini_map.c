/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 10:49:35 by fducrot           #+#    #+#             */
/*   Updated: 2026/05/18 10:49:35 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_filled_square(t_data *data, int px, int py, int color)
{
	int	dx;
	int	dy;
	int	size;

	size = data->mini_map.scale;
	dy = 0;
	while (dy < size)
	{
		dx = 0;
		while (dx < size)
		{
			mm_put_pixel(data, px + dx, py + dy, color);
			dx++;
		}
		dy++;
	}
}

void	draw_mini_map_cells(t_data *data)
{
	int	y;
	int	x;
	int	color;
	int	pixel_x;
	int	pixel_y;

	y = 0;
	while (y < data->map->map_size)
	{
		x = 0;
		while (data->map->map[y] && data->map->map[y][x])
		{
			if (data->mini_map.discovered[y][x])
			{
				color = choose_color_mini_map_cells(data->map->map[y][x]);
				pixel_x = data->mini_map.pos_x + x * data->mini_map.scale;
				pixel_y = data->mini_map.pos_y + y * data->mini_map.scale;
				draw_filled_square(data, pixel_x, pixel_y, color);
			}
			x++;
		}
		y++;
	}
}

static bool	is_in_map_bounds(t_data *data, int y, int x)
{
	if (y < 0 || y >= data->map->map_size)
		return (false);
	if (!data->map->map[y])
		return (false);
	if (x < 0 || x >= (int)ft_strlen(data->map->map[y]))
		return (false);
	return (true);
}

void	change_state_fog_of_war(t_data *data)
{
	int	player_x;
	int	player_y;
	int	dy;
	int	dx;

	player_x = (int)data->raycast->pos_x;
	player_y = (int)data->raycast->pos_y;
	dy = -REVEAL_RADIUS;
	while (dy <= REVEAL_RADIUS)
	{
		dx = -REVEAL_RADIUS;
		while (dx <= REVEAL_RADIUS)
		{
			if (dx * dx + dy * dy <= REVEAL_RADIUS * REVEAL_RADIUS
				&& is_in_map_bounds(data, player_y + dy, player_x + dx))
				data->mini_map.discovered[player_y + dy][player_x + dx] = true;
			dx++;
		}
		dy++;
	}
}

void	draw_mini_map(t_data *data)
{
	draw_mini_map_cells(data);
	draw_mini_map_cone(data);
	draw_mini_map_player(data);
}
