
#include "../../includes/cub3d.h"

static void free_linked_map(t_linked_map *linked_map)
{
	t_linked_map	*temp;

	while (linked_map)
	{
		temp = linked_map;
		linked_map = linked_map->next;
		if (temp->line)
			free(temp->line);
		free(temp);
	}
}

static void free_texture_struct(t_texture *texture)
{
	if (texture)
	{
		if (texture->no_path)
			free(texture->no_path);
		if (texture->so_path)
			free(texture->so_path);
		if (texture->we_path)
			free(texture->we_path);
		if (texture->ea_path)
			free(texture->ea_path);
		if (texture->floor)
			ft_free_2d_array(texture->floor);
		if (texture->ceiling)
			ft_free_2d_array(texture->ceiling);
		free(texture);
	}
}

static void free_map_struct(t_map *map)
{
	if (map)
	{
		if (map->map)
			ft_free_2d_array(map->map);
		if (map->map_copy)
			ft_free_2d_array(map->map_copy);
	
		free(map);
	}
}

static void close_fds(t_data *data)
{
	if (data->fd > 0)
	{
		close(data->fd);
	}
}

void	clean_all(t_data *data)
{
	printf("Cleaning all resources...\n"); // Debug statement
	close_fds(data);
	free_map_struct(data->map);
	free_texture_struct(data->texture);
	free_linked_map(data->linked_map);
	ft_memset(data, 0, sizeof(t_data));
	return ;
}