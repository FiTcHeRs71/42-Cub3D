
#include "../../includes/cub3d.h"

static char	**copy_map(t_data *data, char *line)
{
	char	*temp;
	char	*old_temp;
	char	**args;

	temp = ft_strdup("");
	if (!temp)
		return (NULL);
	while (line)
	{
		old_temp = temp;
		temp = ft_strjoin(temp, line);
		free(old_temp);
		free(line);
		if (!temp)
			return (NULL);
		line = get_next_line(data->fd);
	}
	args = ft_split(temp, '\n');
	free(temp);
	return (args);
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

	if (ft_strncmp(&file[ft_strlen(file + 4)], ".cub", 4))
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
	data->map->map = copy_map(data, line);
	check_map(data, data->map);
}
