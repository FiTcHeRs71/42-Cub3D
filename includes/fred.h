#ifndef FRED_H
# define FRED_H

# include "cub3d_struct.h"

bool	is_wall_at(t_data *data, double px, double py);
void	change_state_fog_of_war(t_data *data);
void	compute_minimap_normal(t_data *data);
void	draw_mini_map(t_data *data);
void	draw_mini_map_player(t_data *data);
void	mm_put_pixel(t_data *data, int x, int y, int color);
void	draw_mini_map_cone(t_data *data);
void	toggle_minimap_fullscreen(t_data *data);
void	load_bonus_textures(t_data *data, t_texture *texture, t_mlx *mlx);
void	toggle_nearest_door(t_data *data);
bool	in_bounds(t_data *data, int y, int x);
#endif