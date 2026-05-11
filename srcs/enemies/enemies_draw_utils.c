
#include "../../includes/cub3d.h"

static void	draw_column(t_data *data, t_sprite_calc *s, int x, t_tex_img *tex)
{
	int	tex_x;
	int	y;
	int	d;
	int	tex_y;
	int	color;

	if (s->transform_y > data->z_buffer[x])
		return ;
	tex_x = (int)((x - (-s->width / 2 + s->screen_x))
			* tex->width / s->width);
	if (tex_x < 0 || tex_x >= tex->width)
		return ;
	y = s->draw_start_y;
	while (y < s->draw_end_y)
	{
		d = (y - s->v_offset) * 256 - data->window_y * 128
			+ s->height * 128;
		tex_y = ((d * tex->height) / s->height) / 256;
		color = get_pixel(tex, tex_x, tex_y);
		put_pixel_sprite(data, x, y, color);
		y++;
	}
}

static void	draw_one_sprite(t_data *data, t_enemy *e)
{
	t_sprite_calc	s;
	t_tex_img		*tex;
	int				x;

	compute_transform(&s, data, e);
	if (s.transform_y <= 0)
		return ;
	compute_screen_bounds(&s, data);
	if (e->is_dead)
		tex = &data->enemy_anim.dead_frame;
	else
		tex = &data->enemy_anim.frames[data->enemy_anim.current_frame];
	x = s.draw_start_x;
	while (x < s.draw_end_x)
	{
		draw_column(data, &s, x, tex);
		x++;
	}
}

void	draw_sprites(t_data *data)
{
	t_enemy	*e;

	sort_enemies(data);
	e = data->enemies;
	while (e)
	{
		draw_one_sprite(data, e);
		e = e->next;
	}
}
