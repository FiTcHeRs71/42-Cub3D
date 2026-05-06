
#include "../../includes/cub3d.h"

static void	move_player(t_data *data, t_raycast *raycast)
{
	(void) data; 
	(void) raycast;
}

void	update_player(t_data *data)
{
	move_player(data, data->raycast);
}