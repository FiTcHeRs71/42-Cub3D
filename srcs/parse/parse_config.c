
#include "../../includes/cub3d.h"

static bool save_color_code(t_data *data, char ***rgb_code, char *line)
{
	int	i;
	char	**temp;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	temp = ft_split(&line[i], ',');
	if (!temp)
	{
		ft_error(MALLOC_FAILED, data);
	}
	i = 0;
	rgb_code = ft_calloc(3, sizeof(char **));
	while (temp[i])
	{
		*(rgb_code)[i] = ft_strtrim(temp[i], "\n");
		if (!rgb_code[i])
			ft_error(MALLOC_FAILED, data);
		i++;
	}
	ft_free_2d_array(temp);
	if (i != 2)
	{
		ft_error(INVALID_SETTINGS, data);
	}
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
	if(!*texture_path)
		ft_error(MALLOC_FAILED, data);
	i = ft_strlen(*texture_path) - 1;
	if (i >= 0 && (*texture_path)[i] == '\n')
		(*texture_path)[i] = '\0';
	return (true);
}

bool	extract_config(char *line, t_data *data)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (true);
	if (ft_strncmp(&line[i], "NO ", 3) == 0)
		return(save_texture(data, &data->texture->no_path, &line[i + 3]));
	else if (ft_strncmp(&line[i], "SO ", 3) == 0)
		return(save_texture(data, &data->texture->so_path, &line[i + 3]));
	else if (ft_strncmp(&line[i], "WE ", 3) == 0)
		return(save_texture(data, &data->texture->we_path, &line[i + 3]));
	else if (ft_strncmp(&line[i], "EA ", 3) == 0)
		return(save_texture(data, &data->texture->ea_path, &line[i + 3]));
	else if (ft_strncmp(&line[i], "F ", 2) == 0)
		return (save_color_code(data, &data->texture->floor, &line[i + 1]));
	else if (ft_strncmp(&line[i], "C ", 2) == 0)
		return (save_color_code(data, &data->texture->ceiling, &line[i + 1]));
	return(false);
}
