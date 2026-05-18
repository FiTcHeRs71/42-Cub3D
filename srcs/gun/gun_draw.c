/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 10:49:18 by fducrot           #+#    #+#             */
/*   Updated: 2026/05/18 10:49:18 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <linux/limits.h>

static t_tex_img	*get_current_frame(t_data *data)
{
	if (data->gun.state == GUN_SHOOT_1)
		return (&data->gun.frames[1]);
	else if (data->gun.state == GUN_SHOOT_2)
		return (&data->gun.frames[2]);
	return (&data->gun.frames[0]);
}

static int	get_tex_color(t_tex_img *tex, int tx, int ty)
{
	char	*pixel;

	if (tx < 0 || tx >= tex->width || ty < 0 || ty >= tex->height)
		return (MAGENTA);
	pixel = tex->addr + ty * tex->size_line + tx * (tex->bpp / 8);
	return (*(unsigned int *)pixel);
}

static void	put_pixel_gun(t_data *data, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x < 0 || x >= data->window_x || y < 0 || y >= data->window_y)
		return ;
	if ((color & 0x00FFFFFF) == MAGENTA)
		return ;
	offset = (y * data->mlx->size_line) + (x * data->mlx->bits_per_pixel / 8);
	pixel = data->mlx->img_data + offset;
	*(unsigned int *)pixel = color;
}

void	draw_gun(t_data *data)
{
	t_tex_img	*frame;
	t_gun_draw	gun_draw;

	ft_memset(&gun_draw, 0, sizeof(t_gun_draw));
	frame = get_current_frame(data);
	gun_draw.gun_size = (int)(data->window_y) * GUN_HEIGHT_RATIO;
	gun_draw.x_start = (data->window_x - gun_draw.gun_size) / 2;
	gun_draw.y_start = data->window_y - gun_draw.gun_size;
	gun_draw.y = 0;
	while (gun_draw.y < gun_draw.gun_size)
	{
		gun_draw.x = 0;
		while (gun_draw.x < gun_draw.gun_size)
		{
			gun_draw.tx = gun_draw.x * frame->width / gun_draw.gun_size;
			gun_draw.ty = gun_draw.y * frame->height / gun_draw.gun_size;
			gun_draw.color = get_tex_color(frame, gun_draw.tx, gun_draw.ty);
			put_pixel_gun(data, gun_draw.x_start + gun_draw.x,
				gun_draw.y_start + gun_draw.y, gun_draw.color);
			gun_draw.x++;
		}
		gun_draw.y++;
	}
}
