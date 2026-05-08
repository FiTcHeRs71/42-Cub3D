
#include "../../includes/cub3d.h"
#include <linux/limits.h>

static t_tex_img	*get_current_frame(t_data *data)
{
	if (data->gun.state == GUN_SHOOT_1)
		return (&data->gun.shoot1);
	else if (data->gun.state == GUN_SHOOT_2)
		return (&data->gun.shoot2);
	return (&data->gun.neutre);
}

static int	get_tex_color(t_tex_img *tex, int tx, int ty)
{
	char	*pixel;
	if (tx < 0 || tx >= tex->width || ty < 0 || ty >= tex->height)
		return (MAGENTA);
	pixel = tex->addr + ty * tex->size_line + tx * (tex->bpp / 8);
	return (*(unsigned int *)pixel);
}

static void	put_pixel_gun(t_data *data, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x < 0 || x >= data->window_x || y < 0 || y >= data->window_y)
		return ;
	if ((color & 0x00FFFFFF) == MAGENTA)
		return ;
	offset = (y * data->mlx->size_line) + (x * data->mlx->bits_per_pixel / 8);
	pixel = data->mlx->img_data + offset;
	*(unsigned int *)pixel = color;
}

void	draw_gun(t_data *data)
{
	t_tex_img	*frame;
	int			gun_size;
	int			x_start;
	int			y_start;
	int			x;
	int			y;
	int			tx;
	int			ty;
	int			color;

	frame = get_current_frame(data);
	gun_size = (int)(data->window_y) * GUN_HEIGHT_RATIO;
	x_start = (data->window_x - gun_size) / 2;
	y_start = data->window_y - gun_size;
	y = 0;
	while (y < gun_size)
	{
		x = 0;
		while (x < gun_size)
		{
			tx = x * frame->width / gun_size;
			ty = y * frame->height / gun_size;
			color = get_tex_color(frame, tx, ty);
			put_pixel_gun(data, x_start + x, y_start + y, color);
			x++;
		}
		y++;
	}
}