#ifndef LEO_H
# define LEO_H

# include "../minilibx-linux/mlx.h"
# include <stdbool.h>

typedef struct s_data t_data;
typedef struct s_map t_map;

typedef struct s_raycast
{
	double	pos_x;
	double	pos_y;
	double	dir_x; // direction vector
	double	dir_y;
	double	plane_x; // 2d raycasting version
	double	plane_y;
	double	time; // used to make movement smoother by using time difference between frames
	double	old_time;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	double	wall_dist;
	int		wall_side;
	bool	is_hit;
	bool	done;
}			t_raycast;

typedef struct s_draw
{
	int		line_h;
	int		line_start;
	int		line_end;
	int		steps;
}			t_draw;

void	draw_wall(t_data *stats, t_raycast *data, t_draw *draw, int x_coord);
void	raycasting(t_data *stats, t_map *map);

#endif