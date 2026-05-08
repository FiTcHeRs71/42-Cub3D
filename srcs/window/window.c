
#include "../../includes/cub3d.h"

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		data->threads[i].stats = data;
		data->threads[i].x_start = i * data->window_x / 9;
		if (i == 8)
			data->threads[i].x_end = data->window_x;
		else
			data->threads[i].x_end = (i + 1) * data->window_x / 9;
		i++;
	}
	i = 0;
	while (i < 9)
	{
		pthread_create(&data->threads[i].id, NULL, raycasting, &data->threads[i]);
		i++;
	}
}

int	game_loop(t_data *data)
{
	int	i;

	i = 0;
	update_player(data);
	clear_image(data);
	create_threads(data);
	while (i < 9)
	{
		pthread_join(data->threads[i].id, NULL);
		i++;
	}
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
	load_wall_textures(data, data->texture, data->mlx);
	mlx_loop_hook(mlx->mlx_connect, game_loop, data);
	mlx_hook(mlx->mlx_window, 2, 1L << 0, handle_key_press, data);
	mlx_hook(mlx->mlx_window, 3, 1L << 1, handle_key_release, data);
	mlx_hook(mlx->mlx_window, 17, 0, close_window, data);
	mlx_hook(mlx->mlx_window, 6, 1L << 6, mouse_motion, data);
	mlx_hook(mlx->mlx_window, 9, 1L << 21, focus_in, data);
	mlx_hook(mlx->mlx_window, 10, 1L << 21, focus_out, data);
	mlx_mouse_hide(mlx->mlx_connect, mlx->mlx_window);
	mlx_mouse_move(mlx->mlx_connect, mlx->mlx_window, data->window_x / 2, data->window_y / 2);
	mlx->img = mlx_new_image(mlx->mlx_connect, data->window_x, data->window_y);
	if (!mlx->img)
		ft_error(MINI_LBX, data);
	mlx->img_data = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel,
			&mlx->size_line, &mlx->endian);
}

