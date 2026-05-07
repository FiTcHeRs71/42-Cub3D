
#include "../../includes/cub3d.h"

void	clean_mini_map(t_data *data)
{
	int	i;

	i = 0;
	if (data->mini_map.discovered)
	{
		while (i < data->map->map_size)
		{
			free(data->mini_map.discovered[i]);
			i++;
		}
		free(data->mini_map.discovered);
	}
}
