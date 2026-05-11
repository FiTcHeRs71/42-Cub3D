
#include "../../includes/cub3d.h"

void	release_mouse(t_data *data)
{
	mlx_mouse_show(data->mlx->mlx_connect, data->mlx->mlx_window);
	data->mouse_active = false;
}

int	handle_key_press(int keycode, t_data *data)
{
	if (keycode == XK_w)
		data->keys.w = true;
	else if (keycode == XK_a)
		data->keys.a = true;
	else if (keycode == XK_s)
		data->keys.s = true;
	else if (keycode == XK_d)
		data->keys.d = true;
	else if (keycode == XK_e)
		toggle_nearest_door(data);
	else if (keycode == XK_Left)
		data->keys.left = true;
	else if (keycode == XK_Right)
		data->keys.right = true;
	else
		handler_bonus_key(keycode, data);
	return (0);
}

int	handle_key_release(int keycode, t_data *data)
{
	if (keycode == XK_w)
		data->keys.w = false;
	else if (keycode == XK_a)
		data->keys.a = false;
	else if (keycode == XK_s)
		data->keys.s = false;
	else if (keycode == XK_d)
		data->keys.d = false;
	else if (keycode == XK_Left)
		data->keys.left = false;
	else if (keycode == XK_Right)
		data->keys.right = false;
	return (0);
}

int	focus_in(t_data *data)
{
	reset_mouse_to_center(data);
	return (0);
}

int	focus_out(t_data *data)
{
	data->mouse_active = false;
	return (0);
}
