
#include "../../includes/cub3d.h"

static void copy_map(t_data *data, char *line)
{
	char	*tmp;
	while (line)
	{
		while (line[0] == '\n')
		{
			free(line);
			line = get_next_line(data->fd);
		}
		tmp = ft_strtrim(line, "\n");
		node_map_add_back(&data->linked_map, new_node_map(ft_strdup(tmp)));
		free(tmp);
		free(line);
		if (!data->linked_map || !data->linked_map->line)
			ft_error(MALLOC_FAILED, data);
		line = get_next_line(data->fd);
	}
}

static void	init_struct(t_data *data)
{
	data->map = ft_calloc(1, sizeof(t_map));
	data->texture = ft_calloc(1, sizeof(t_texture));
	if (!data->map || !data->texture)
	{
		ft_error(MALLOC_FAILED, data);
	}
}

void	parse_cub3d(t_data *data, char *file)
{
	char	*line;
	int		config_count;

	if (ft_strncmp(&file[ft_strlen(file) - 4], ".cub", 4))
	{
		ft_error("File map has to be .cub\n", data);
	}
	data->fd = open(file, O_RDONLY);
	if (data->fd < 0)
	{
		ft_error(FD_ERROR, data);
	}
	init_struct(data);
	config_count = 0;
	line = get_next_line(data->fd);
	while (line)
	{
		if (config_count < 6)
		{
			if (extract_config(line, data))
			{
				if (line[0] != '\n' && line[0] != '\0') 
					config_count++;
			}
			else
				ft_error(INVALID_SETTINGS, data);
		}
		else
		{
			break ;
		}
		free(line);
		line = get_next_line(data->fd);
	}
	data->texture->rgb_floor = get_color_code(data, data->texture->floor);
	data->texture->rgb_ceiling = get_color_code(data, data->texture->ceiling);
	copy_map(data, line);
	check_map(data, data->map);
}
