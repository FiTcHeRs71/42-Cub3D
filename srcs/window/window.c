
# include "../../includes/cub3d.h"

 int   game_loop(t_data *data)
{
	int i;

	i = 0;
	while (i < data->window_x * data->window_y)
	{
		((unsigned int *)data->mlx->img_data)[i] = 0xFF0000;
		i++;
	}
	mlx_put_image_to_window(data->mlx->mlx_connect, data->mlx->mlx_window,data->mlx->img, 0, 0);
	return (0);
}
void	init_window(t_data *data, t_mlx *mlx)
{
	mlx->mlx_connect = mlx_init();
	if(!mlx->mlx_connect)
		ft_error(MINI_LBX, data);
	mlx_get_screen_size(mlx->mlx_connect,&data->window_x, &data->window_y);
	mlx->mlx_window = mlx_new_window(mlx->mlx_connect, data->window_x, data->window_y, TITLE);
	if (!mlx->mlx_window)
		ft_error(MINI_LBX, data);
	mlx_loop_hook(mlx->mlx_connect, game_loop, data);
	mlx_key_hook(mlx->mlx_window, handle_keyboard_input, data);
	mlx_hook(mlx->mlx_window, 17, 0, close_window, data);
	mlx->img = mlx_new_image(mlx->mlx_connect, data->window_x, data->window_y);
	if (!mlx->img)
		ft_error(MINI_LBX, data);
	mlx->img_data = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->size_line, &mlx->endian);
}