
#include "../../includes/cub3d.h"

int	handler_bonus_key(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	else if (keycode == XK_Tab)
	{
		if (data->mouse_active)
			release_mouse(data);
		else
			reset_mouse_to_center(data);
	}
	else if (keycode == XK_m)
		toggle_minimap_fullscreen(data);
	else if (keycode == XK_e)
		toggle_nearest_door(data);
	return (0);
}
