
#include "../../includes/cub3d.h"

void	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->mlx = ft_calloc(1, sizeof(t_mlx));
	data->raycast = ft_calloc(1, sizeof(t_raycast));
	data->draw = ft_calloc(1, sizeof(t_draw));
	data->map = ft_calloc(1, sizeof(t_map));
	data->texture = ft_calloc(1, sizeof(t_texture));
	data->threads = ft_calloc(10, sizeof(t_thread_data));
	if (!data->mlx || !data->raycast || !data->map || !data->texture)
		ft_error(ERR_MALLOC, data);
	data->mouse_active = true;
}

void	init_mini_map(t_data *data)
{
	int	i;

	i = 0;
	data->mini_map.fullscreen = false;
	compute_minimap_normal(data);
	data->mini_map.discovered = ft_calloc(data->map->map_size, sizeof(bool *));
	if (!data->mini_map.discovered)
		ft_error(ERR_MALLOC, data);
	while (i < data->map->map_size)
	{
		data->mini_map.discovered[i] = ft_calloc(
			ft_strlen(data->map->map[i]) + 1, sizeof(bool));
		if (!data->mini_map.discovered[i])
			ft_error(ERR_MALLOC, data);
		i++;
	}
}
