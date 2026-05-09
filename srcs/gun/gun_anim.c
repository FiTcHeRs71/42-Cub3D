
#include "../../includes/cub3d.h"

void	update_gun_animation(t_data *data)
{
	if (data->gun.state == GUN_IDLE)
		return ;
	data->gun.frame_counter++;
	if (data->gun.frame_counter < GUN_ANIM_FRAMES)
		return ;
	data->gun.frame_counter = 0;
	if (data->gun.state == GUN_SHOOT_1)
		data->gun.state = GUN_SHOOT_2;
	else if (data->gun.state == GUN_SHOOT_2)
		data->gun.state = GUN_IDLE;
}

int	mouse_press(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1 && data->gun.state == GUN_IDLE)
	{
		data->gun.state = GUN_SHOOT_1;
		data->gun.frame_counter = 0;
	}
	return (0);
}
