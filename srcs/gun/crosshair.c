#include "../../includes/cub3d.h"

static void	put_pixel_hud(t_data *data, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x < 0 || x >= data->window_x || y < 0 || y >= data->window_y)
		return ;
	offset = (y * data->mlx->size_line)
		+ (x * (data->mlx->bits_per_pixel / 8));
	pixel = data->mlx->img_data + offset;
	*(unsigned int *)pixel = color;
}

void	draw_crosshair(t_data *data)
{
	int	cx;
	int	cy;
	int	i;
	int	t;

	cx = data->window_x / 2;
	cy = data->window_y / 1.9;
	t = CROSSHAIR_THICKNESS / 2;
	i = -CROSSHAIR_SIZE;
	while (i <= CROSSHAIR_SIZE)
	{
		put_pixel_hud(data, cx + i, cy, CROSSHAIR_COLOR);
		put_pixel_hud(data, cx, cy + i, CROSSHAIR_COLOR);
		if (t > 0)
		{
			put_pixel_hud(data, cx + i, cy + 1, CROSSHAIR_COLOR);
			put_pixel_hud(data, cx + 1, cy + i, CROSSHAIR_COLOR);
		}
		i++;
	}
}