
#include "../../includes/cub3d.h"

#include "../../includes/cub3d.h"

void	load_bonus_textures(t_data *data, t_texture *texture, t_mlx *mlx)
{
	texture->door.img = mlx_xpm_file_to_image(mlx->mlx_connect,
			"./images/wall/door.xpm",
			&texture->door.width, &texture->door.height);
	if (!texture->door.img)
		ft_error_ctx("Texture", "./images/wall/door.xpm", data);
	texture->door.addr = mlx_get_data_addr(texture->door.img,
			&texture->door.bpp, &texture->door.size_line, &texture->door.endian);
	texture->ground.img = mlx_xpm_file_to_image(mlx->mlx_connect,
			"./images/ceiling_floor/floor.xpm",
			&texture->ground.width, &texture->ground.height);
	if (!texture->ground.img)
		ft_error_ctx("Texture", "./images/ceiling_floor/floor.xpm", data);
	texture->ground.addr = mlx_get_data_addr(texture->ground.img,
			&texture->ground.bpp, &texture->ground.size_line, &texture->ground.endian);
	texture->ceiling.img = mlx_xpm_file_to_image(mlx->mlx_connect,
			"./images/ceiling_floor/ceiling.xpm",
			&texture->ceiling.width, &texture->ceiling.height);
	if (!texture->ceiling.img)
		ft_error_ctx("Texture", "./images/ceiling_floor/ceiling.xpm", data);
	texture->ceiling.addr = mlx_get_data_addr(texture->ceiling.img,
			&texture->ceiling.bpp, &texture->ceiling.size_line, &texture->ceiling.endian);
}
