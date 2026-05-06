
#include "../../includes/cub3d.h"

void	load_textures(t_data *data, t_texture *texture, t_mlx *mlx)
{
	texture->no.img = mlx_xpm_file_to_image(mlx->mlx_connect, texture->no_path,
			&texture->no.width, &texture->no.height);
	texture->so.img = mlx_xpm_file_to_image(mlx->mlx_connect, texture->so_path,
			&texture->so.width, &texture->so.height);
	texture->ea.img = mlx_xpm_file_to_image(mlx->mlx_connect, texture->ea_path,
			&texture->ea.width, &texture->ea.height);
	texture->we.img = mlx_xpm_file_to_image(mlx->mlx_connect, texture->we_path,
			&texture->we.width, &texture->we.height);
	if (!texture->no.img || !texture->so.img || !texture->ea.img || !texture->we.img)
		ft_error(NO_ACCES, data);
	printf("NO: %p | SO: %p | WE: %p | EA: %p\n", texture->no.img,
		texture->so.img, texture->we.img, texture->ea.img); // a vire- debuger*/
}