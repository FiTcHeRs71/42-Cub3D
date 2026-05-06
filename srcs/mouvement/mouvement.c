
#include "../../includes/cub3d.h"

static void	move_player(t_data *data, t_raycast *r)
{
	if (data->keys.w)
	{
		move_up(data, r);
	}
	if (data->keys.s)
	{
		move_down(data, r);
	}
	if (data->keys.d)
	{
		move_right(data, r);
	}
	if (data->keys.a)
	{
		move_left(data, r);
	}
}

static void rotate_player(t_data *data, t_raycast *r)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	rot = 0;
	if (data->keys.left)
		rot = -ROT_SPEED;
	else if (data->keys.right)
		rot = ROT_SPEED;
	if (rot == 0)
		return ;
	old_dir_x   = r->dir_x;
	r->dir_x    = r->dir_x * cos(rot) - r->dir_y * sin(rot);
	r->dir_y    = old_dir_x * sin(rot) + r->dir_y * cos(rot);
	old_plane_x = r->plane_x;
	r->plane_x  = r->plane_x * cos(rot) - r->plane_y * sin(rot);
	r->plane_y  = old_plane_x * sin(rot) + r->plane_y * cos(rot);
}

void	update_player(t_data *data)
{
	move_player(data, data->raycast);
	rotate_player(data, data->raycast);
}