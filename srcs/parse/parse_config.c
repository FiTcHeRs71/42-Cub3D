
#include "../../includes/cub3d.h"

static bool	is_valid_color_code(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
/**
 * @brief checks that the code is valid and performs the bit shifting.
 * 
 * Checks that the code contains only numbers.
 * Converts ASCII characters to integers.
 * did the bit shifting.
 * 
 * @param data  Pointer to the main structure where parsed data is stored.
 * @param array_code Double pointer or where is the code stored.
 */
int	get_color_code(t_data *data, char **array_code)
{
	int	i;
	int	rgb_code[3];
	int	bit_rgb;

	i = 0;
	while (array_code[i])
	{
		if (!is_valid_color_code(array_code[i]))
			ft_error(INVALID_SETTINGS, data);
		rgb_code[i] = ft_atoi(array_code[i]);
		if (rgb_code[i] > 255 || rgb_code[i] < 0)
			ft_error(INVALID_SETTINGS, data);
		i++;
	}
	bit_rgb = (rgb_code[0] << 16) | (rgb_code[1] << 8) | (rgb_code[2] << 0);
	return (bit_rgb);
}
/**
 * @brief Splits and stores an RGB color string into the texture structure.
 *
 * Splits the line by ',' expecting exactly 3 components (R, G, B),
 * trims whitespace from each, and allocates the result into rgb_code.
 *
 * @param data      Pointer to the main structure (used for error handling).
 * @param rgb_code  Output double pointer where the split color array is stored.
 * @param line      Raw color string to parse (e.g. "255,128,0").
 * @return true on success, false otherwise.
 */
static bool	save_color_code(t_data *data, char ***rgb_code, char *line)
{
	int		i;
	char	**temp;

	temp = ft_split(&line[0], ',');
	if (!temp)
		ft_error(MALLOC_FAILED, data);
	i = ft_array_size(temp);
	if (i != 3)
	{
		ft_free_2d_array(temp);
		ft_error(INVALID_SETTINGS, data);
	}
	*(rgb_code) = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (temp[i])
	{
		(*rgb_code)[i] = ft_strtrim(temp[i], " \n\t");
		if (!(*rgb_code)[i])
			ft_error(MALLOC_FAILED, data);
		i++;
	}
	(*rgb_code)[i] = NULL;
	ft_free_2d_array(temp);
	return (true);
}

static bool	save_texture(t_data *data, char **texture_path, char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (false);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (*texture_path != NULL)
		return (false);
	*texture_path = ft_strdup(&line[i]);
	if (!*texture_path)
		ft_error(MALLOC_FAILED, data);
	i = ft_strlen(*texture_path) - 1;
	if (i >= 0 && (*texture_path)[i] == '\n')
		(*texture_path)[i] = '\0';
	return (true);
}
/**
 * @brief Parses a single configuration line and stores the corresponding value.
 *
 * Identifies the identifier (NO, SO, WE, EA, F, C) and dispatches
 * to save_texture or save_color_code. Skips empty and whitespace-only lines.
 *
 * @param line  The raw line read from the .cub file.
 * @param data  Pointer to the main structure where config is stored.
 * @return true if the line is valid or empty, false if unrecognized.
 */
bool	extract_config(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (true);
	if (ft_strncmp(&line[i], "NO ", 3) == 0)
		return (save_texture(data, &data->texture->no_path, &line[i + 3]));
	else if (ft_strncmp(&line[i], "SO ", 3) == 0)
		return (save_texture(data, &data->texture->so_path, &line[i + 3]));
	else if (ft_strncmp(&line[i], "WE ", 3) == 0)
		return (save_texture(data, &data->texture->we_path, &line[i + 3]));
	else if (ft_strncmp(&line[i], "EA ", 3) == 0)
		return (save_texture(data, &data->texture->ea_path, &line[i + 3]));
	else if (ft_strncmp(&line[i], "F ", 2) == 0)
		return (save_color_code(data, &data->texture->floor, &line[i + 1]));
	else if (ft_strncmp(&line[i], "C ", 2) == 0)
		return (save_color_code(data, &data->texture->ceiling, &line[i + 1]));
	return (false);
}
