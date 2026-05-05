
#include "../../includes/cub3d.h"

void	load_textures(t_data *data, t_texture *texture, t_mlx *mlx)
{
	texture->no_wall = mlx_xpm_file_to_image(mlx->mlx_connect, texture->no_path, &texture->width, &texture->height);
	texture->so_wall = mlx_xpm_file_to_image(mlx->mlx_connect, texture->so_path, &texture->width, &texture->height);
	texture->we_wall = mlx_xpm_file_to_image(mlx->mlx_connect, texture->we_path, &texture->width, &texture->height);
	texture->ea_wall = mlx_xpm_file_to_image(mlx->mlx_connect, texture->ea_path, &texture->width, &texture->height);
	if (! texture->ea_wall || !texture->we_wall || !texture->so_wall || !texture->no_wall)
		ft_error(NO_ACCES, data);
	printf("NO: %p | SO: %p | WE: %p | EA: %p\n",
		texture->no_wall, texture->so_wall, texture->we_wall, texture->ea_wall); // a virer - debuger
}