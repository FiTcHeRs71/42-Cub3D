#include "../../includes/cub3d.h"

static void	compute_shoot_transform(t_shoot_calc *s, t_data *data, t_enemy *e)
{
	t_raycast	*r;
	double		sprite_x;
	double		sprite_y;
	double		inv_det;

	r = data->raycast;
	sprite_x = e->pos_x - r->pos_x;
	sprite_y = e->pos_y - r->pos_y;
	inv_det = 1.0 / (r->plane_x * r->dir_y - r->dir_x * r->plane_y);
	s->transform_x = inv_det * (r->dir_y * sprite_x - r->dir_x * sprite_y);
	s->transform_y = inv_det
		* (-r->plane_y * sprite_x + r->plane_x * sprite_y);
	s->screen_x = (int)((data->window_x / 2)
			* (1 + s->transform_x / s->transform_y));
	s->width = abs((int)(data->window_y / s->transform_y)) * SPRITE_SCALE;
}

static bool	is_targeted(t_data *data, t_enemy *e, t_shoot_calc *s)
{
	int	center;
	int	half_w;

	if (e->is_dead)
		return (false);
	compute_shoot_transform(s, data, e);
	if (s->transform_y <= 0 || s->transform_y > SHOOT_RANGE)
		return (false);
	if (s->transform_y > data->z_buffer[data->window_x / 2])
		return (false);
	center = data->window_x / 2;
	half_w = s->width / 2;
	if (center < s->screen_x - half_w || center > s->screen_x + half_w)
		return (false);
	return (true);
}

static t_enemy	*find_target(t_data *data)
{
	t_enemy			*e;
	t_enemy			*best;
	t_shoot_calc	s;
	double			best_dist;

	best = NULL;
	best_dist = SHOOT_RANGE;
	e = data->enemies;
	while (e)
	{
		if (is_targeted(data, e, &s))
		{
			if (s.transform_y < best_dist)
			{
				best_dist = s.transform_y;
				best = e;
			}
		}
		e = e->next;
	}
	return (best);
}

void	try_shoot(t_data *data)
{
	t_enemy	*target;

	target = find_target(data);
	if (!target)
	{
		printf("MISS\n");
		return ;
	}
	target->is_dead = true;  // ← on activera ça à l'étape C
}