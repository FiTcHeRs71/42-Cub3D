
#include "../../includes/cub3d.h"

void	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
	data->mlx = ft_calloc(1, sizeof(t_mlx));
	data->raycast = ft_calloc(1, sizeof(t_raycast));
	data->draw = ft_calloc(1, sizeof(t_draw));
	data->map = ft_calloc(1, sizeof(t_map));
	data->texture = ft_calloc(1, sizeof(t_texture));
	if (!data->mlx || !data->raycast || !data->map || !data->texture)
		ft_error(MALLOC_FAILED, data);
	data->mouse_active = true;
}

void	init_mini_map(t_data *data)
{
	int	i;

	i = 0;
	data->mini_map.width = data->window_x * 0.15;
	data->mini_map.height = data->window_y * 0.15;
	data->mini_map.scale = data->mini_map.width / data->largest_line;
	data->mini_map.pos_x = data->window_x - data->mini_map.width - 10;
	data->mini_map.pos_y = 10;
	data->mini_map.discovered = ft_calloc(data->map->map_size, sizeof(bool *));
	if (!data->mini_map.discovered)
		ft_error(MALLOC_FAILED, data);
	while (i < data->map->map_size)
	{
		data->mini_map.discovered[i] = ft_calloc(ft_strlen(data->map->map[i])+ 1, sizeof(bool));
		if (!data->mini_map.discovered[i])
			ft_error(MALLOC_FAILED, data);
		i++;
	}
}
