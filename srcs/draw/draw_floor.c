#include "../../includes/cub3d.h"

static void	put_pixel_ceiling(t_data *data, t_floor *ground)
{
	t_tex_img	ceiling_tex;
	char		*pixel;
	int			offset;
	int			color;

	ceiling_tex = data->texture->ceiling;
	if (ground->screen_x < 0 || ground->screen_x >= data->window_x
		|| ground->ceiling_y < 0 || ground->ceiling_y >= data->window_y)
		return ;
	if (ground->tex_x < 0 || ground->tex_x >= ceiling_tex.width
		|| ground->tex_y < 0 || ground->tex_y >= ceiling_tex.height)
		return ;
	offset = (ground->ceiling_y * data->mlx->size_line) + (ground->screen_x
			* (data->mlx->bits_per_pixel / 8));
	pixel = data->mlx->img_data + offset;
	color = *(unsigned int *)(ceiling_tex.addr + ground->tex_y
			* ceiling_tex.size_line + ground->tex_x * (ceiling_tex.bpp / 8));
	*(unsigned int *)pixel = color;
}

static void	put_pixel_ground(t_data *data, t_floor *ground)
{
	t_tex_img	ground_tex;
	char		*pixel;
	int			offset;
	int			color;

	ground_tex = data->texture->ground;
	if (ground->screen_x < 0 || ground->screen_x >= data->window_x
		|| ground->screen_y < 0 || ground->screen_y >= data->window_y)
		return ;
	if (ground->tex_x < 0 || ground->tex_x >= ground_tex.width
		|| ground->tex_y < 0 || ground->tex_y >= ground_tex.height)
		return ;
	offset = (ground->screen_y * data->mlx->size_line) + (ground->screen_x
			* (data->mlx->bits_per_pixel / 8));
	pixel = data->mlx->img_data + offset;
	color = *(unsigned int *)(ground_tex.addr + ground->tex_y
			* ground_tex.size_line + ground->tex_x * (ground_tex.bpp / 8));
	*(unsigned int *)pixel = color;
}

static void	init_background_data(t_thread_data *td, t_floor *ground,
		t_data *data, t_raycast *ray)
{
	double	horizon_d;

	ground->ceiling_y = data->window_y - ground->screen_y - 1;
	horizon_d = ground->screen_y - data->window_y / 2.0;
	ground->row_distance = data->window_y / 2 / horizon_d;
	ground->left_ray_x = ray->dir_x - ray->plane_x;
	ground->left_ray_y = ray->dir_y - ray->plane_y;
	ground->right_ray_x = ray->dir_x + ray->plane_x;
	ground->right_ray_y = ray->dir_y + ray->plane_y;
	ground->floor_x = ray->pos_x + ground->row_distance * ground->left_ray_x;
	ground->floor_y = ray->pos_y + ground->row_distance * ground->left_ray_y;
	ground->floor_step_x = ground->row_distance * (ground->right_ray_x
			- ground->left_ray_x) / data->window_x;
	ground->floor_step_y = ground->row_distance * (ground->right_ray_y
			- ground->left_ray_y) / data->window_x;
	ground->floor_x += td->x_start * ground->floor_step_x;
	ground->floor_y += td->x_start * ground->floor_step_y;
	ground->screen_x = td->x_start;
}

void	draw_background(t_thread_data *td, t_raycast *ray)
{
	t_tex_img	tex;
	t_floor		ground;
	t_data		*data;

	ft_memset(&ground, 0, sizeof(t_floor));
	data = td->data;
	tex = data->texture->ground;
	ground.screen_y = data->window_y / 2 + 1;
	while (ground.screen_y < data->window_y - 1)
	{
		init_background_data(td, &ground, data, ray);
		while (ground.screen_x < td->x_end)
		{
			ground.tex_x = (int)((ground.floor_x - floor(ground.floor_x))
					* tex.width);
			ground.tex_y = (int)((ground.floor_y - floor(ground.floor_y))
					* tex.height);
			put_pixel_ground(data, &ground);
			put_pixel_ceiling(data, &ground);
			ground.floor_x += ground.floor_step_x;
			ground.floor_y += ground.floor_step_y;
			ground.screen_x++;
		}
		ground.screen_y++;
	}
}
