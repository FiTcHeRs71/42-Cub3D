
# include "../../includes/cub3d.h"

void	init_window(t_data *data, t_mlx *mlx)
{
	mlx->mlx_connect = mlx_init();
	if(!mlx->mlx_connect)
		ft_error(MINI_LBX, data);
	mlx_get_screen_size(mlx->mlx_connect,&data->window_x, &data->window_y);
	mlx->mlx_window = mlx_new_window(mlx->mlx_connect, data->window_x, data->window_y, TITLE);
	if (!mlx->mlx_window)
		ft_error(MINI_LBX, data);
	mlx_key_hook(mlx->mlx_window, handle_keyboard_input, mlx);
	mlx_hook(mlx->mlx_window, 17, 0, close_window, mlx);
}