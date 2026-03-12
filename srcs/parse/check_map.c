
#include "../../includes/cub3d.h"

static void	count_and_check_flags(char *line, t_data *data)
{
	size_t i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("10NSEW", line[i]))
		{
			if (data->player_flag > 0)
			{
				ft_error("Error : Multiple player in map, exit\n", data);
			}
			data->player_flag = 1;
		}
		i++;
	}
	
}

static void	check_arg(char *line, t_data *data)
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
		count_and_check_flags(line[i], data);
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