
#include "../../includes/cub3d.h"

void	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->mlx = ft_calloc(1, sizeof(t_mlx));
	data->raycast = ft_calloc(1, sizeof(t_raycast)); // a free
	data->draw = ft_calloc(1, sizeof(t_draw));       // a free
	if (!data->mlx || !data->raycast)
		ft_error(MALLOC_FAILED, data);
}