#ifndef FRED_H
# define FRED_H

# include "cub3d_struct.h"

void	init_window(t_data *data, t_mlx *mlx);
int	handle_keyboard_input(int keycode, t_mlx *mlx);
int	close_window(t_mlx *mlx, t_data *data);

#endif