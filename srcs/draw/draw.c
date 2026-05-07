
#include "../../includes/cub3d.h"

void	put_pixel(t_data *stats, t_raycast *data, int y_coord, int x_coord)
{
	t_tex_img	tex;
	char		*pixel;
	int			offset;
	int			color;

	(void)data;
	tex = stats->texture->tex_flag;
	if (x_coord < 0 || x_coord >= stats->window_x || y_coord < 0 || y_coord >= stats->window_y)
		return ;
	if (stats->texture->tex_x < 0 || stats->texture->tex_x >= tex.width
		|| stats->texture->tex_y < 0 || stats->texture->tex_y >= tex.height)
		return ;
	color = *(unsigned int *)(tex.addr + stats->texture->tex_y * tex.size_line + stats->texture->tex_x * (tex.bpp / 8));
	offset = (y_coord * stats->mlx->size_line) + (x_coord * (stats->mlx->bits_per_pixel / 8));
	pixel = stats->mlx->img_data + offset;
	if ((data->wall_side == 0 && data->ray_dir_x > 0) || (data->wall_side == 1 && data->ray_dir_y > 0))
		color = (color >> 1) & 0x7F7F7F;
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
	int	y;

	y = draw->line_start;
	use_texture(stats, data, stats->texture);
	if (draw->steps == 0)
		draw->steps = 1;
	while (y < draw->line_end)
	{
		stats->texture->tex_y = (int)stats->texture->tex_pos;
		stats->texture->tex_pos += stats->texture->step;
		put_pixel(stats, data, y, x_coord);
		y++;
	}
}
