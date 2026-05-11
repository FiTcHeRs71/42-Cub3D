
#include "../../includes/cub3d.h"

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		data->threads[i].data = data;
		data->threads[i].x_start = i * data->window_x / 9;
		if (i == 8)
			data->threads[i].x_end = data->window_x;
		else
			data->threads[i].x_end = (i + 1) * data->window_x / 9;
		i++;
	}
	i = 0;
	while (i < 9)
	{
		pthread_create(&data->threads[i].id, NULL, raycasting,
			&data->threads[i]);
		i++;
	}
}
