#ifndef FRED_H
# define FRED_H

# include "cub3d_struct.h"

int	handle_key_press(int keycode, t_data *data);
int	handle_key_release(int keycode, t_data *data);
void	update_player(t_data *data);
bool	can_move(t_data *data, double new_x, double mew_y);
void	move_up(t_data *data, t_raycast *r);
void	move_down(t_data *data, t_raycast *r);
void	move_left(t_data *data, t_raycast *r);
void	move_right(t_data *data, t_raycast *r);









#endif