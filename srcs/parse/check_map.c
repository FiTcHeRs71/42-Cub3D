
#include "../../includes/cub3d.h"

void	check_arg(char *line, t_data *data)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isascii(line[i]))
		{
			ft_error("only ascii parameters.\n", data);
		}
		if (!ft_strchr("10NSEW", line[i]))
		{
			ft_error("Invalid parameters.\n", data);
		}
		//ft_count_and_check_args(line[i], data); des trucs a compter ?
		i++;
	}
}

void	check_map(t_data *data)
{
	size_t	i;
	int		size;

	i = 0;
	while (data->map[i])
	{
		check_arg(data->map[i], data);
		i++;
	}
	//valide_path(data); // flood_fill ?
}