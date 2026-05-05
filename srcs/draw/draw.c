
#include "../../includes/cub3d.h"


void	put_pixel(t_data *stats, t_raycast *data, int y_coord, int x_coord)
{
	char	*pixel;
	int		offset;
	int		i;

	if (x_coord < 0 || x_coord >= stats->window_x || y_coord < 0 || y_coord >= stats->window_y)
		return ;
	i = y_coord * stats->window_y + x_coord;
	offset = (y_coord * stats->mlx->size_line) + (x_coord * (stats->mlx->bits_per_pixel / 8));
	pixel = stats->mlx->img_data + offset;
	if (data->wall_side == 1)
		*(unsigned int *)pixel = 0xFF / 2;
	else
		*(unsigned int *)pixel = 0xFF;
}

void	draw_wall(t_data *stats, t_raycast *data, t_draw *draw, int x_coord)
{
	int	i;
	int	dy;
	int	y_inc;
	int	new_y;

	i = 0;
	new_y = draw->line_start;
	dy = draw->line_end - draw->line_start;
	draw->steps = fabs(dy);
	if (draw->steps == 0)
		draw->steps = 1;
	y_inc = dy / draw->steps;
	while (i <= draw->steps)
	{
		put_pixel(stats, data, new_y, x_coord);
		new_y += y_inc;
		i++;
	}
}

// texture 64x64