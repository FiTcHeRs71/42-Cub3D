
#include "../../includes/cub3d.h"

void	put_pixel(t_data *stats, t_raycast *data, int y_coord, int x_coord)
{
	t_tex_img	tex;
	char		*pixel;
	int			offset;
	int			color;

	tex = stats->texture->tex_flag;
	color = *(unsigned int *)(tex.addr + stats->texture->tex_y * tex.size_line + stats->texture->tex_x * (tex.bpp / 8));
	if (x_coord < 0 || x_coord >= stats->window_x || y_coord < 0 || y_coord >= stats->window_y)
		return ;
	offset = (y_coord * stats->mlx->size_line) + (x_coord * (stats->mlx->bits_per_pixel / 8));
	pixel = stats->mlx->img_data + offset;
	if (data->wall_side == 1)
		*(unsigned int *)pixel = color / 2;
	else
		*(unsigned int *)pixel = color;
}

void	put_pixel_floor(t_data *stats, t_raycast *data, int y_coord, int x_coord)
{
	char	*pixel;
	int		offset;

	if (x_coord < 0 || x_coord >= stats->window_x || y_coord < 0 || y_coord >= stats->window_y)
		return ;
	offset = (y_coord * stats->mlx->size_line) + (x_coord * (stats->mlx->bits_per_pixel / 8));
	pixel = stats->mlx->img_data + offset;
	if (data->wall_side == 1)
		*(unsigned int *)pixel = stats->texture->rgb_floor;
	else
		*(unsigned int *)pixel = stats->texture->rgb_floor;
}

void	put_pixel_ceiling(t_data *stats, t_raycast *data, int y_coord, int x_coord)
{
	char	*pixel;
	int		offset;

	if (x_coord < 0 || x_coord >= stats->window_x || y_coord < 0 || y_coord >= stats->window_y)
		return ;
	offset = (y_coord * stats->mlx->size_line) + (x_coord * (stats->mlx->bits_per_pixel / 8));
	pixel = stats->mlx->img_data + offset;
	if (data->wall_side == 1)
		*(unsigned int *)pixel = stats->texture->rgb_ceiling;
	else
		*(unsigned int *)pixel = stats->texture->rgb_ceiling;
}

void	draw_floor(t_data *stats, t_raycast *data, t_draw *draw, int x_coord)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (i < draw->line_start)
	{
		put_pixel_floor(stats, data, y, x_coord);
		y++;
		i++;
	}
}

void	draw_ceiling(t_data *stats, t_raycast *data, t_draw *draw, int x_coord)
{
	int	i;
	int	y;

	i = draw->line_end;
	y = draw->line_end;
	while (i < stats->window_y)
	{
		put_pixel_ceiling(stats, data, y, x_coord);
		y++;
		i++;
	}
}

void	draw_wall(t_data *stats, t_raycast *data, t_draw *draw, int x_coord)
{
	int	i;
	int	dy;
	int	y_inc;
	int	new_y;

	i = 0;
	new_y = draw->line_start;
	dy = draw->line_end - draw->line_start;
	draw->steps = abs(dy);
	use_texture(stats, data, stats->texture);
	if (draw->steps == 0)
		draw->steps = 1;
	y_inc = dy / draw->steps;
	while (i <= draw->steps)
	{
		stats->texture->tex_y = (int)stats->texture->tex_pos;
		stats->texture->tex_pos += stats->texture->step;
		put_pixel(stats, data, new_y, x_coord);
		new_y += y_inc;
		i++;
	}
}

// texture 64x64