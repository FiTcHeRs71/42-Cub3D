/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 12/05/2026 10:27:10 by fducrot           #+#    #+#             */
/*   Updated: 18/05/2026 10:47:45 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	put_pixel(t_data *data, t_draw *draw, int y_coord, int x_coord)
{
	t_tex_img	texture;
	char		*pixel;
	int			offset;
	int			color;

	texture = draw->tex.tex_flag;
	if (x_coord < 0 || x_coord >= data->window_x || y_coord < 0
		|| y_coord >= data->window_y)
		return ;
	if (draw->tex.tex_x < 0 || draw->tex.tex_x >= texture.width
		|| draw->tex.tex_y < 0 || draw->tex.tex_y >= texture.height)
		return ;
	color = *(unsigned int *)(texture.addr + draw->tex.tex_y * texture.size_line
			+ draw->tex.tex_x * (texture.bpp / 8));
	offset = (y_coord * data->mlx->size_line) + (x_coord
			* (data->mlx->bits_per_pixel / 8));
	pixel = data->mlx->img_data + offset;
	if ((draw->wall_side == 0 && draw->raydir_x > 0) || (draw->wall_side == 1
			&& draw->raydir_y > 0))
		color = (color >> 1) & 0x7F7F7F;
	*(unsigned int *)pixel = color;
}

void	draw_wall(t_data *data, t_raycast *ray, t_draw *draw, int x_coord)
{
	int	y;

	draw->tex.no = data->texture->no;
	draw->tex.so = data->texture->so;
	draw->tex.ea = data->texture->ea;
	draw->tex.we = data->texture->we;
	draw->tex.door = data->texture->door;
	y = draw->line_start;
	use_texture(data, ray, &draw->tex, draw);
	if (draw->steps == 0)
		draw->steps = 1;
	while (y < draw->line_end)
	{
		draw->tex.tex_y = (int)draw->tex.tex_pos;
		draw->tex.tex_pos += draw->tex.step;
		put_pixel(data, draw, y, x_coord);
		y++;
	}
}
