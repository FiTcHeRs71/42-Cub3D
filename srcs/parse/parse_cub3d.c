
#include "../../includes/cub3d.h"
#include <fcntl.h>
#include <math.h>

bool	checker_file_extension(char *file, char *extension)
{
	int	fd;

	if (ft_strlen(file) < 4)
		return (false);
	if (ft_strncmp(&file[ft_strlen(file) - 4], extension, 4))
		return (false);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (false);
	close(fd);
	return (true);
}

static void	add_map_line(t_data *data, char **line)
{
	char			*temp;
	char			*dup;
	t_linked_map	*node;

	temp = ft_strtrim(*line, "\n");
	if (!temp)
	{
		free(*line);
		ft_error(ERR_MALLOC, data);
	}
	dup = ft_strdup(temp);
	free(temp);
	if (!dup)
	{
		free(*line);
		ft_error(ERR_MALLOC, data);
	}
	node = new_node_map(dup);
	if (!node)
	{
		free(dup);
		free(*line);
		ft_error(ERR_MALLOC, data);
	}
	node_map_add_back(&data->linked_map, node);
}

static void	copy_map(t_data *data, char *line)
{
	bool	map_end;

	map_end = false;
	while (line && ft_is_whitespace(line) == 1)
		line = free_and_getline(line, data->fd);
	while (line)
	{
		if (ft_is_whitespace(line) == 1)
			map_end = true;
		else
		{
			if (map_end)
			{
				free(line);
				ft_error(ERR_MAP_EMPTY_LINE, data);
			}
			add_map_line(data, &line);
		}
		line = free_and_getline(line, data->fd);
	}
}
/**
 * @brief opens the map file and parses the elements.
 *
 * Records the absolute path to the NORT, SOUTH, EAST, and WEST textures
 * Copy the map contained in the file into a linked list
 * Saves and converts RGB codes for the floor and ceiling.
 *
 * @param data  Pointer to the main structure where parsed data is stored.
 */
static void	fill_config(t_data *data)
{
	char	*line;
	int		config_count;

	line = get_next_line(data->fd);
	config_count = 0;
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
			{
				free(line);
				ft_error(ERR_CFG_FORMAT, data);
			}
		}
		else
			break ;
		line = free_and_getline(line, data->fd);
	}
	if (config_count < 6)
		ft_error(ERR_CFG_MISSING, data);
	copy_map(data, line);
}


/**
 * @brief Parses and validates the .cub configuration file.
 *
 * Checks that the file has a .cub extension, opens it, initializes
 * the map and texture structures, extracts the configuration settings
 * and map data, validates the map, then computes the RGB color codes
 * for the floor and ceiling.
 *
 * @param data  Pointer to the main structure where parsed data is stored.
 * @param file  Path to the .cub file to parse.
 */
void	parse_cub3d(t_data *data, char *file)
{
	if (!checker_file_extension(file, ".cub"))
		ft_error(ERR_FILE_EXT, data);
	data->fd = open(file, O_RDONLY);
	if (data->fd < 0)
	{
		ft_error(ERR_FILE_OPEN, data);
	}
	fill_config(data);
	close(data->fd);
	data->fd = 0;
	check_map(data, data->map);
	data->texture->rgb_floor = get_color_code(data, data->texture->floor);
	data->texture->rgb_ceiling = get_color_code(data, data->texture->ceiling);
	set_data_raycasting(data->raycast, data->map);
}
