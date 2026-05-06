
# include "../../includes/cub3d.h"

int	key_release(int keycode, t_data *data)
{
	data->keys[keycode] = false;
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	printf("---%i--- | keycode\n", keycode);
	data->keys[keycode] = true;
	if (keycode == XK_Escape)
	{
			close_window(data);
	}
	if (keycode == XK_w || keycode == XK_Up)
	{

	}
	if (keycode == XK_a || keycode == XK_Left)
	{

	}
	if (keycode == XK_s || keycode == XK_Down)
	{

	}
	if (keycode == XK_d || keycode == XK_Right)
	{

	}
	return (0);
}