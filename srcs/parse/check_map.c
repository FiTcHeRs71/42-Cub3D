
#include "../../includes/cub3d.h"

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
		if (line[i] == 'N')
		{

		}
	}
}

void	check_map(t_data *data)
{
	size_t	i;

	i = 0;
	while (data->map[i])
	{
		check_arg(data->map[i], data);
		i++;
	}
	//valide_path(data); // flood_fill ?
}