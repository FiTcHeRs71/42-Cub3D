#ifndef FRED_H
# define FRED_H

# include "../minilibx-linux/mlx.h"
# include "cub3d_struct.h"

# define MINI_LBX "Error related to the mini libx\n"

void	init_window(t_data *data, t_mlx *mlx);
int	handle_keyboard_input(int keycode, t_mlx *mlx);
int	close_window(t_mlx *mlx, t_data *data);
void	init_data(t_data *data);
#endif