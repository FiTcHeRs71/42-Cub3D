
#include "../../includes/cub3d.h"

static void	check_arg(char *line, t_data *data, int y)
{
	size_t	i;

	i = 0;
	if (line[0] == '\0')
		ft_error(INVALID_MAP, data);
	while (line[i])
	{
		if (!ft_isascii(line[i]) || (!ft_strchr(" 01NSEW\n\t", line[i])))
			ft_error("Invalid parameters in map.\n", data);
		if (ft_strchr("NSEW", line[i]))
		{
			if (ft_strchr("N", line[i]))
				data->map->payer_dir = NORTH;
			if (ft_strchr("S", line[i]))
				data->map->payer_dir = SOUTH;
			if (ft_strchr("W", line[i]))
				data->map->payer_dir = WEST;
			if (ft_strchr("E", line[i]))
				data->map->payer_dir = EAST;
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
		ft_error(MALLOC_FAILED, data);
	}
	i = 0;
	while (original[i])
	{
		copy[i] = ft_strdup(original[i]);
		if (!copy[i])
		{
			ft_free_2d_array(copy);
			ft_error(MALLOC_FAILED, data);
		}
		i++;
	}
	copy[i] = NULL;
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
	if (y < 0 || x < 0 || x >= (int)ft_strlen(map->map_copy[y])
		|| y >= node_map_size(data->linked_map))
	{
		ft_error(INVALID_MAP, data);
	}
	if (!map->map_copy[y] || !map->map_copy[y][x])
	{
		ft_error(INVALID_MAP, data);
	}
	if (map->map_copy[y][x] == '1' || map->map_copy[y][x] == 'X')
	{
		return ;
	}
	if (map->map_copy[y][x] != '0' && !ft_strchr("NSEW", map->map_copy[y][x]))
	{
		ft_error(INVALID_MAP, data);
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
	map->map = ft_calloc(node_map_size(data->linked_map) + 1, sizeof(char *));
	if (!map->map)
		ft_error(MALLOC_FAILED, data);
	convert_linked_map_to_array(data, map);
	while (map->map[i])
	{
		check_arg(map->map[i], data, i);
		i++;
	}
	if (map->player_flag != 1)
		ft_error(NB_PLAYER, data);
	map->map_copy = flood_fill_copy_map(data, map->map);
	flood_fill_valid_map(data, map, map->player_y, map->player_x);
	printf("good MAP\n");
}
