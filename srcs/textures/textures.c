
#include "../../includes/cub3d.h"

void	load_wall_textures(t_data *data, t_texture *texture, t_mlx *mlx)
{
	texture->no.img = mlx_xpm_file_to_image(mlx->mlx_connect, texture->no_path,
			&texture->no.width, &texture->no.height);
	texture->no.addr = mlx_get_data_addr(texture->no.img, &texture->no.bpp,
			&texture->no.size_line, &texture->no.endian);
	texture->so.img = mlx_xpm_file_to_image(mlx->mlx_connect, texture->so_path,
			&texture->so.width, &texture->so.height);
	texture->so.addr = mlx_get_data_addr(texture->so.img, &texture->so.bpp,
			&texture->so.size_line, &texture->so.endian);
	texture->ea.img = mlx_xpm_file_to_image(mlx->mlx_connect, texture->ea_path,
			&texture->ea.width, &texture->ea.height);
	texture->ea.addr = mlx_get_data_addr(texture->ea.img, &texture->ea.bpp,
			&texture->ea.size_line, &texture->ea.endian);
	texture->we.img = mlx_xpm_file_to_image(mlx->mlx_connect, texture->we_path,
			&texture->we.width, &texture->we.height);
	texture->we.addr = mlx_get_data_addr(texture->we.img, &texture->we.bpp,
			&texture->we.size_line, &texture->we.endian);
	if (!texture->no.img)
		ft_error_ctx("Texture", texture->no_path, data);
	if (!texture->so.img)
		ft_error_ctx("Texture", texture->so_path, data);
	if (!texture->ea.img)
		ft_error_ctx("Texture", texture->ea_path, data);
	if (!texture->we.img)
		ft_error_ctx("Texture", texture->we_path, data);
}

void	finalise_tex_data(t_data *data, t_texture *tex, t_draw *draw, t_raycast *ray)
{
	if (ray->wall_side == 0)
	{
		if (ray->ray_dir_x > 0)
			tex->tex_flag = tex->ea;
		else
			tex->tex_flag = tex->we;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			tex->tex_flag = tex->so;
		else
			tex->tex_flag = tex->no;
	}
	tex->step = 1.0 * tex->tex_flag.height / draw->line_h;
	tex->tex_pos = (draw->line_start - data->window_y / 2 + draw->line_h / 2) * tex->step;
}

void	use_texture(t_data *data, t_raycast *ray, t_texture *tex)
{
	if (ray->wall_side == 0)
		tex->wall_x = ray->pos_y + ray->wall_dist * ray->ray_dir_y;
	else
		tex->wall_x = ray->pos_x + ray->wall_dist * ray->ray_dir_x;
	tex->wall_x = tex->wall_x - floor(tex->wall_x);
	finalise_tex_data(data, tex, data->draw, ray);
	tex->tex_x = (int)(tex->wall_x * (double)(tex->tex_flag.width));
	if (ray->wall_side == 0 && ray->ray_dir_x > 0)
		tex->tex_x = tex->tex_flag.width - tex->tex_x - 1;
	if (ray->wall_side == 1 && ray->ray_dir_y > 0)
		tex->tex_x = tex->tex_flag.width - tex->tex_x - 1;
}

void	clear_image(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->mlx->size_line * data->window_y)
	{
		data->mlx->img_data[i] = 0;
		i++;
	}
}
