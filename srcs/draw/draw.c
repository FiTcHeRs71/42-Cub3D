
#include "../../includes/cub3d.h"

void	put_pixel(t_data *stats, t_draw *draw, int y_coord, int x_coord)
{
	t_tex_img	texture;
	char		*pixel;
	int			offset;
	int			color;

	texture = draw->tex.tex_flag;
	if (draw->tex.tex_x < 0 || draw->tex.tex_x >= texture.width
		|| draw->tex.tex_y < 0 || draw->tex.tex_y >= texture.height)
		return ;
	color = *(unsigned int *)(texture.addr + draw->tex.tex_y * texture.size_line
			+ draw->tex.tex_x * (texture.bpp / 8));
	offset = (y_coord * stats->mlx->size_line)
		+ (x_coord * (stats->mlx->bits_per_pixel / 8));
	pixel = stats->mlx->img_data + offset;
	if ((draw->wall_side == 0 && draw->raydir_x > 0)
		|| (draw->wall_side == 1 && draw->raydir_y > 0))
		color = (color >> 1) & 0x7F7F7F;
	*(unsigned int *)pixel = color;
}

void	put_pixel_floor(t_data *stats, t_raycast *data, int y_coord, int x_coord)
{
	char	*pixel;
	int		offset;

	(void)data;
	offset = (y_coord * stats->mlx->size_line)
		+ (x_coord * (stats->mlx->bits_per_pixel / 8));
	pixel = stats->mlx->img_data + offset;
	*(unsigned int *)pixel = stats->texture->rgb_floor;
}

void	put_pixel_ceiling(t_data *stats, t_raycast *data, int y_coord, int x_coord)
{
	char	*pixel;
	int		offset;

	(void)data;
	offset = (y_coord * stats->mlx->size_line)
		+ (x_coord * (stats->mlx->bits_per_pixel / 8));
	pixel = stats->mlx->img_data + offset;
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

	draw->tex.no = stats->texture->no;
	draw->tex.so = stats->texture->so;
	draw->tex.ea = stats->texture->ea;
	draw->tex.we = stats->texture->we;
	draw->tex.door = stats->texture->door;
	draw->raydir_x = data->ray_dir_x;
	draw->raydir_y = data->ray_dir_y;
	draw->wall_side = data->wall_side;
	y = draw->line_start;
	use_texture(stats, data, &draw->tex, draw);
	if (draw->steps == 0)
	draw->steps = 1;
	while (y < draw->line_end)
	{
		draw->tex.tex_y = (int)draw->tex.tex_pos;
		draw->tex.tex_pos += draw->tex.step;
		put_pixel(stats, draw, y, x_coord);
		y++;
	}
}
