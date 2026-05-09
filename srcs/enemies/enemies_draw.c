
#include "../../includes/cub3d.h"

void	compute_transform(t_sprite_calc *s, t_data *data, t_enemy *e)
{
	t_raycast	*r;

	r = data->raycast;
	s->sprite_x = e->pos_x - r->pos_x;
	s->sprite_y = e->pos_y - r->pos_y;
	s->inv_det = 1.0 / (r->plane_x * r->dir_y - r->dir_x * r->plane_y);
	s->transform_x = s->inv_det
		* (r->dir_y * s->sprite_x - r->dir_x * s->sprite_y);
	s->transform_y = s->inv_det
		* (-r->plane_y * s->sprite_x + r->plane_x * s->sprite_y);
}

void	compute_screen_bounds(t_sprite_calc *s, t_data *data)
{
	s->screen_x = (int)((data->window_x / 2)
			* (1 + s->transform_x / s->transform_y));
	s->height = abs((int)(data->window_y / s->transform_y)) * SPRITE_SCALE;
	s->width  = abs((int)(data->window_y / s->transform_y)) * SPRITE_SCALE;
	s->v_offset = s->height / 2;
	s->draw_start_y = -s->height / 2 + data->window_y / 2 + s->v_offset;
	if (s->draw_start_y < 0)
		s->draw_start_y = 0;
	s->draw_end_y = s->height / 2 + data->window_y / 2 + s->v_offset;
	if (s->draw_end_y >= data->window_y)
		s->draw_end_y = data->window_y - 1;
	s->draw_start_x = -s->width / 2 + s->screen_x;
	if (s->draw_start_x < 0)
		s->draw_start_x = 0;
	s->draw_end_x = s->width / 2 + s->screen_x;
	if (s->draw_end_x >= data->window_x)
		s->draw_end_x = data->window_x - 1;
}

int	get_pixel(t_tex_img *tex, int tx, int ty)
{
	char	*p;

	if (tx < 0 || tx >= tex->width || ty < 0 || ty >= tex->height)
		return (MAGENTA);
	p = tex->addr + ty * tex->size_line + tx * (tex->bpp / 8);
	return (*(unsigned int *)p);
}

void	put_pixel_sprite(t_data *data, int x, int y, int color)
{
	char	*pixel;
	int		offset;

	if (x < 0 || x >= data->window_x || y < 0 || y >= data->window_y)
		return ;
	if ((color & 0x00FFFFFF) == MAGENTA)
		return ;
	offset = (y * data->mlx->size_line)
		+ (x * (data->mlx->bits_per_pixel / 8));
	pixel = data->mlx->img_data + offset;
	*(unsigned int *)pixel = color;
}