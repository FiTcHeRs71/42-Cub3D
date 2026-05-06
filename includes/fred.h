#ifndef FRED_H
# define FRED_H

# include "cub3d_struct.h"

int	handle_key_press(int keycode, t_data *data);
int	handle_key_release(int keycode, t_data *data);
void	update_player(t_data *data);
#endif