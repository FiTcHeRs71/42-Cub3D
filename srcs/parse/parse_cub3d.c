
#include "../../includes/cub3d.h"

void	check_line_empty(t_data *data, char *map)
{
	size_t	i;

	i = 0;
	while (map[i])
	{
		if (map[i] == '\n' && map[i + 1] == '\n')
		{
			ft_error(INVALID_MAP, data);
		}
		i++;
	}
}
char	**copy_map(t_data *data)
{
	char	*line;
	char	*temp;
	char	*old_temp;
	char	**args;

	temp = ft_strdup("");
	if (!temp)
		return (NULL);
	line = get_next_line(data->fd);
	while (line)
	{
		if (line[0] == '\n')
			ft_error(INVALID_MAP, data);
		old_temp = temp;
		temp = ft_strjoin(temp, line);
		free(old_temp);
		free(line);
		if (!temp)
			return (NULL);
		line = get_next_line(data->fd);
	}
	check_line_empty(data, temp);
	args = ft_split(temp, '\n');
	free(temp);
	return (args);
}

void	parse_cub3d(t_data *data, char *file)
{
	if (ft_strncmp(file[ft_strlen(file + 4)], ".cub", 4))
	{
		ft_error("File map has to be .cub\n", data);
	}
	data->fd = open(file, O_RDONLY);
	if (data->fd < 0)
	{
		ft_error(FD_ERROR, data);
	}
	data->map = copy_map(data);
	if (!data->map || !data->map[0])
	{
		ft_error(INVALID_MAP, data);
	}
	check_map(data);
}
