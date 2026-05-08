
#include "../../includes/cub3d.h"

#include "../../includes/cub3d.h"

void	load_door_textures(t_data *data, t_texture *texture, t_mlx *mlx)
{
	texture->door.img = mlx_xpm_file_to_image(mlx->mlx_connect,
			"./images/wall/door.xpm",
			&texture->door.width, &texture->door.height);
	if (!texture->door.img)
		ft_error_ctx("Texture", "./images/wall/door.xpm", data);
	texture->door.addr = mlx_get_data_addr(texture->door.img,
			&texture->door.bpp, &texture->door.size_line, &texture->door.endian);
}