
#include "../../includes/cub3d.h"
#include <sys/param.h>

void	draw_mini_map_player(t_data *data)
{
	int	pixel_x;
	int	pixel_y;
	int	dx;
	int	dy;
	int	size;

	size = 5;
	pixel_x = data->mini_map.pos_x
		+ (int)(data->raycast->pos_x * data->mini_map.scale);
	pixel_y = data->mini_map.pos_y
		+ (int)(data->raycast->pos_y * data->mini_map.scale);
	dy = -size / 2;
	while (dy <= size / 2)
	{
		dx = -size / 2;
		while (dx <= size / 2)
		{
			mm_put_pixel(data, pixel_x + dx, pixel_y + dy, MM_COLOR_PLAYER);
			dx++;
		}
		dy++;
	}
}

static void	bresenham_step(int p[5], int *x0, int *y0)
{
	int	e2;

	e2 = 2 * p[4];
	if (e2 >= p[1])
	{
		p[4] += p[1];
		*x0 += p[2];
	}
	if (e2 <= p[0])
	{
		p[4] += p[0];
		*y0 += p[3];
	}
}

static void	draw_line(t_data *data, int x0, int y0, int x1, int y1)
{
	int	p[5];

	p[0] = abs(x1 - x0);
	p[1] = -abs(y1 - y0);
	p[2] = (x0 < x1) ? 1 : -1;
	p[3] = (y0 < y1) ? 1 : -1;
	p[4] = p[0] + p[1];
	while (1)
	{
		mm_put_pixel(data, x0, y0, MM_COLOR_CONE);
		if (x0 == x1 && y0 == y1)
			break ;
		bresenham_step(p, &x0, &y0);
	}
}

void	draw_mini_map_cone(t_data *data)
{
	int		px;
	int		py;
	int		left_x;
	int		left_y;
	double	len;

	len = data->mini_map.scale * MM_CONE_LENGTH;
	px = data->mini_map.pos_x
		+ (int)(data->raycast->pos_x * data->mini_map.scale);
	py = data->mini_map.pos_y
		+ (int)(data->raycast->pos_y * data->mini_map.scale);
	left_x = px + (int)((data->raycast->dir_x + data->raycast->plane_x) * len);
	left_y = py + (int)((data->raycast->dir_y + data->raycast->plane_y) * len);
	draw_line(data, px, py, left_x, left_y);
	left_x = px + (int)((data->raycast->dir_x - data->raycast->plane_x) * len);
	left_y = py + (int)((data->raycast->dir_y - data->raycast->plane_y) * len);
	draw_line(data, px, py, left_x, left_y);
}

void	compute_minimap_fullscreen(t_data *data)
{
	data->mini_map.scale = min(data->window_x / data->largest_line, data->window_y / data->map->map_size);
	data->mini_map.width = data->mini_map.scale * data->largest_line;
	data->mini_map.height = data->mini_map.scale * data->map->map_size;
	data->mini_map.pos_x = (data->window_x - data->mini_map.width) / 2;
	data->mini_map.pos_x = (data->window_y - data->mini_map.height) / 2;
}

void	toggle_minimap_fullscreen(t_data *data)
{
	data->mini_map.fullscreen = !data->mini_map.fullscreen;
	if (data->mini_map.fullscreen)
		compute_minimap_fullscreen(data);
	else
		compute_minimap_normal(data);
}