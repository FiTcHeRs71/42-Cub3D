
#include "../../includes/cub3d.h"

void	load_gun_textures(t_data *data)
{
	void	*conn;

	conn = data->mlx->mlx_connect;
	data->gun.neutre.img = mlx_xpm_file_to_image(conn, "./images/guns/gun_neutre.xpm", &data->gun.neutre.width, &data->gun.neutre.height);
	if (!data->gun.neutre.img)
		ft_error_ctx("Texture", "./images/guns/gun_neutre.xpm", data);
	data->gun.neutre.addr = mlx_get_data_addr(data->gun.neutre.img, &data->gun.neutre.bpp, &data->gun.neutre.size_line, &data->gun.neutre.endian);
	data->gun.shoot1.img = mlx_xpm_file_to_image(conn, "./images/guns/gun-shoot-1.xpm", &data->gun.shoot1.width, &data->gun.shoot1.height);
	if (!data->gun.shoot1.img)
		ft_error_ctx("Texture", "./images/guns/gun_shoot_1.xpm", data);
	data->gun.shoot1.addr = mlx_get_data_addr(data->gun.shoot1.img, &data->gun.shoot1.bpp, &data->gun.shoot1.size_line, &data->gun.shoot1.endian);
	data->gun.shoot2.img = mlx_xpm_file_to_image(conn, "./images/guns/gun-shoot-2.xpm", &data->gun.shoot2.width, &data->gun.shoot2.height);
	if (!data->gun.shoot2.img)
		ft_error_ctx("Texture", "./images/guns/gun_shoot_2.xpm", data);
	data->gun.shoot2.addr = mlx_get_data_addr(data->gun.shoot2.img, &data->gun.shoot2.bpp, &data->gun.shoot2.size_line, &data->gun.shoot2.endian);
}