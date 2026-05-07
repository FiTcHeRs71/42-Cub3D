
#include "../../includes/cub3d.h"
#include <stdbool.h>

void	reset_mouse_to_center(t_data *data)
{
	mlx_mouse_hide(data->mlx->mlx_connect, data->mlx->mlx_window);
	mlx_mouse_move(data->mlx->mlx_connect, data->mlx->mlx_window, data->window_x / 2, data->window_y / 2);
	data->mouse_active = true;
}

int	game_loop(t_data *data)
{
	update_player(data);
	clear_image(data);
	change_state_fog_of_war(data);
	raycasting(data, data->raycast, data->draw);
	draw_mini_map(data);
	mlx_put_image_to_window(data->mlx->mlx_connect, data->mlx->mlx_window,
		data->mlx->img, 0, 0);
	return (0);
}
void	init_window(t_data *data, t_mlx *mlx)
{
	mlx->mlx_connect = mlx_init();
	if (!mlx->mlx_connect)
		ft_error(MINI_LBX, data);
	mlx_get_screen_size(mlx->mlx_connect, &data->window_x, &data->window_y);
	mlx->mlx_window = mlx_new_window(mlx->mlx_connect, data->window_x,
			data->window_y, TITLE);
	if (!mlx->mlx_window)
		ft_error(MINI_LBX, data);
	mlx_loop_hook(mlx->mlx_connect, game_loop, data);
	mlx_hook(mlx->mlx_window, 2, 1L << 0, handle_key_press, data);
	mlx_hook(mlx->mlx_window, 3, 1L << 1, handle_key_release, data);
	mlx_hook(mlx->mlx_window, 17, 0, close_window, data);
	mlx_hook(mlx->mlx_window, 6, 1L << 6, mouse_motion, data);
	mlx_hook(mlx->mlx_window, 9, 1L << 21, focus_in, data);
	mlx_hook(mlx->mlx_window, 10, 1L << 21, focus_out, data);
	reset_mouse_to_center(data);
	mlx->img = mlx_new_image(mlx->mlx_connect, data->window_x, data->window_y);
	if (!mlx->img)
		ft_error(MINI_LBX, data);
	mlx->img_data = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->size_line, &mlx->endian);
}

