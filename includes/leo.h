#ifndef LEO_H
# define LEO_H

typedef struct s_floor
{
	double	row_distance;
	double	floor_x;
	double	floor_y;
	double	ceiling_y;
	double	floor_step_x;
	double	floor_step_y;
	double	left_ray_x;
	double	left_ray_y;
	double	right_ray_x;
	double	right_ray_y;
	int		screen_x;
	int		screen_y;
	int		tex_x;
	int		tex_y;
}			t_floor;

void	draw_floor(t_data *data, t_draw *draw, int x_coord);
void	draw_ceiling(t_data *data, t_draw *draw, int x_coord);
void	clear_image(t_data *data);
void	put_pixel(t_data *data, t_draw *draw, int y_coord, int x_coord);

#endif
