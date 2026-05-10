#ifndef FRED_H
# define FRED_H

# include "cub3d_struct.h"

void	clean_wall_and_door(t_texture *texture, t_mlx *mlx);
void	clean_enemies_and_gun(t_mlx *mlx, t_gun *gun, t_enemy_anim *enemy);
#endif