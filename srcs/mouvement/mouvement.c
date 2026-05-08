
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

static void	apply_rotation(t_raycast *r, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = r->dir_x;
	r->dir_x = r->dir_x * cos(rot) - r->dir_y * sin(rot);
	r->dir_y = old_dir_x * sin(rot) + r->dir_y * cos(rot);
	old_plane_x = r->plane_x;
	r->plane_x = r->plane_x * cos(rot) - r->plane_y * sin(rot);
	r->plane_y = old_plane_x * sin(rot) + r->plane_y * cos(rot);
}

static void	rotate_player(t_data *data, t_raycast *r)
{
	double	rot;

	rot = 0;
	if (data->keys.left)
		rot = -ROT_SPEED;
	else if (data->keys.right)
		rot = ROT_SPEED;
	if (rot == 0)
		return ;
	apply_rotation(r, rot);
}

int	mouse_motion(int x, int y, t_data *data)
{
	int	delta_x;
	double	rot;

	(void)y;
	if (!data->mouse_active || !data->raycast)
		return (0);
	delta_x = x - (data->window_x / 2);
	if (delta_x == 0)
		return (0);
	if (delta_x > MOUSE_MAX_DELTA)
		delta_x = MOUSE_MAX_DELTA;
	if (delta_x < -MOUSE_MAX_DELTA)
		delta_x = -MOUSE_MAX_DELTA;
	rot = delta_x * MOUSE_SENSITIVITY;
	apply_rotation(data->raycast, rot);
	reset_mouse_to_center(data);
	return (0);
}

void	update_player(t_data *data)
{
	move_player(data, data->raycast);
	rotate_player(data, data->raycast);
}
