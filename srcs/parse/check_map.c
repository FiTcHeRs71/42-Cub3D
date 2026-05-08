
#include "../../includes/cub3d.h"

/**
 * @brief Validates the map's characters and counts player occurrences.
 *
 * Checks each character in the map line for validity
 * (only ' ', '0', '1', 'N', 'S', 'E', 'W' are allowed).
 * @param line  The current line of the map being checked.
 * @param data  Pointer to the main structure (used for error handling and player info).
 * @param y     The current row index in the map (used for player position).
 */
static void	check_arg(char *line, t_data *data, int y)
{
	size_t	i;

	i = 0;
	if (line[0] == '\0')
		ft_error(ERR_MAP_EMPTY_LINE, data);
	while (line[i])
	{
		if (!ft_isascii(line[i]) || (!ft_strchr(" 01NSEWDd\n\t", line[i])))
			ft_error(ERR_MAP_CHAR, data);
		if (ft_strchr("NSEW", line[i]))
		{
			if (ft_strchr("N", line[i]))
				data->map->player_dir = NORTH;
			if (ft_strchr("S", line[i]))
				data->map->player_dir = SOUTH;
			if (ft_strchr("W", line[i]))
				data->map->player_dir = WEST;
			if (ft_strchr("E", line[i]))
				data->map->player_dir = EAST;
			data->map->player_x = i;
			data->map->player_y = y;
			data->map->player_flag += 1;
		}
		i++;
	}
}

static char	**flood_fill_copy_map(t_data *data, char **original)
{
	char	**copy;
	int		i;

	i = 0;
	while (original[i])
		i++;
	copy = ft_calloc(i + 1, sizeof(char *));
	if (!copy)
	{
		ft_error(ERR_MALLOC, data);
	}
	i = 0;
	while (original[i])
	{
		copy[i] = ft_strdup(original[i]);
		if (!copy[i])
		{
			ft_free_2d_array(copy);
			ft_error(ERR_MALLOC, data);
		}
		i++;
	}
	return (copy);
}
/**
 * @brief Recursively validates map boundaries using a flood fill algorithm.
 *
 * Starting from the player's position, marks visited cells with 'X' and
 * explores all 4 directions. Exits with an error if a cell goes out of
 * bounds or hits an invalid character, ensuring the map is fully enclosed.
 *
 * @param data  Pointer to the main structure (used for error handling).
 * @param map   Pointer to the map structure containing the working copy.
 * @param y     Current row index.
 * @param x     Current column index.
 */
static void	flood_fill_valid_map(t_data *data, t_map *map, int y, int x)
{
	if (y < 0 || x < 0 || y >= map->map_size || x >= (int)ft_strlen(map->map_copy[y]))
	{
		ft_error(ERR_MAP_NOT_CLOSED, data);
	}
	if (!map->map_copy[y] || !map->map_copy[y][x])
	{
		ft_error(ERR_MAP_NOT_CLOSED, data);
	}
	if (map->map_copy[y][x] == '1' || map->map_copy[y][x] == 'X' || map->map_copy[y][x] == ' ')
		return ;
	if (map->map_copy[y][x] != '0' && !ft_strchr("NSEWDd", map->map_copy[y][x]))
	{
		ft_error(ERR_MAP_NOT_CLOSED, data);
	}
	map->map_copy[y][x] = 'X';
	flood_fill_valid_map(data, map, y - 1, x);
	flood_fill_valid_map(data, map, y + 1, x);
	flood_fill_valid_map(data, map, y, x - 1);
	flood_fill_valid_map(data, map, y, x + 1);
}

/**
 * @brief Convert the map into a linked list and verify its validity.
 *
 * Saves the map to an array (char**).
 * Copy the map to another array to perform a flood fill.
 *
 * @param data Pointer to the main structure where parsed data is stored.
 * @param map Pointer to the structure where the map and player info is stored.
 */
void	check_map(t_data *data, t_map *map)
{
	int	i;

	i = 0;
	map->map_size = node_map_size(data->linked_map);
	map->map = ft_calloc(map->map_size + 1, sizeof(char *));
	if (!map->map)
		ft_error(ERR_MALLOC, data);
	convert_linked_map_to_array(data, map);
	while (map->map[i])
	{
		check_arg(map->map[i], data, i);
		if ((int)ft_strlen(map->map[i]) > data->largest_line)
			data->largest_line = ft_strlen(map->map[i]);
		i++;
	}
	if (map->player_flag != 1)
		ft_error(ERR_MAP_PLAYER, data);
	map->map_copy = flood_fill_copy_map(data, map->map);
	flood_fill_valid_map(data, map, map->player_y, map->player_x);
}

char	*free_and_getline(char *line, int fd)
{
	if (line)
		free(line);
	line = get_next_line(fd);
	return (line);
}