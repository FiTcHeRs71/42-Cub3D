#include "../../includes/cub3d.h"

void	draw_floor(t_data *data, t_draw *draw, int x_coord)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (i < draw->line_start)
	{
		put_pixel_floor(data, draw, y, x_coord);
		y++;
		i++;
	}
}

// void	put_pixel_floor(t_data *data, t_draw *draw, t_floor *floor)
// {
// 	t_texture	texture;
// 	char		*pixel;
// 	int			offset;
// 	int			color;

// 	texture = data->texture->floor;
// 	if (x_coord < 0 || x_coord >= data->window_x || y_coord < 0 || y_coord >= data->window_y)
// 		return ;
// 	if ( draw->tex.tex_x < 0 ||  draw->tex.tex_x >= texture.width
// 		||  draw->tex.tex_y < 0 ||  draw->tex.tex_y >= texture.height)
// 		return ;
// 	color = *(unsigned int *)(texture.addr +  draw->tex.tex_y * texture.size_line +  draw->tex.tex_x * (texture.bpp / 8));
// 	offset = (y_coord * data->mlx->size_line) + (x_coord * (data->mlx->bits_per_pixel / 8));
// 	pixel = data->mlx->img_data + offset;
// 	if ((draw->wall_side == 0 && draw->raydir_x > 0) || (draw->wall_side == 1 && draw->raydir_y > 0))
// 		color = (color >> 1) & 0x7F7F7F;
// 	*(unsigned int *)pixel = color;
// 	color = *(unsigned int *)(texture.addr + draw->tex.tex_y * texture.size_line + draw->tex.tex_x * (texture.bpp / 8));
// }

void	draw_f(t_data *data, t_raycast *ray, t_draw *draw, t_texture *tex)
{
	t_floor	floor;
	double	horizon_d;

	ft_memset(&floor, 0, sizeof(t_floor));
	floor.screen_y = data->window_y / 2;
	while (floor.screen_y < data->window_y - 1)
	{
		floor.ceiling_y = data->window_y - floor.screen_y - 1;
		horizon_d = floor.screen_y - data->window_y / 2.0;
		floor.row_distance = data->window_y / 2 / horizon_d;
		floor.left_ray_x = ray->dir_x - ray->plane_x;
		floor.left_ray_y = ray->dir_y - ray->plane_y;
		floor.right_ray_x = ray->dir_x + ray->plane_x;
		floor.right_ray_y = ray->dir_y + ray->plane_y;
		floor.floor_x = ray->pos_x + floor.row_distance * floor.left_ray_x;
		floor.floor_y = ray->pos_y + floor.row_distance * floor.left_ray_y;
		floor.floor_step_x = floor.row_distance * (floor.right_ray_x - floor.left_ray_x) / data->window_x;
		floor.floor_step_y = floor.row_distance * (floor.right_ray_y - floor.left_ray_y) / data->window_x;
		floor.screen_x = 0;
		while (floor.screen_x < data->window_x)
		{
			floor.tex_x = (floor.floor_x - (int)floor.floor_x) / tex->floor.width;
			floor.tex_y = (floor.floor_y - (int)floor.floor_y) / tex->floor.height;
			put_pixel_floor(data, draw, &floor);
			floor.floor_x += floor.floor_step_x;
			floor.floor_y += floor.floor_step_y;
			floor.screen_x++;
		}
		floor.screen_y++;
	}
}
