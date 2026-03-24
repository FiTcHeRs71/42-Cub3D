
#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_data data;

	if (argc != 2)
	{
		ft_putstr_fd(INSTRUCTIONS, 2);
		return (1);
	}
	ft_memset(&data, 0, sizeof(data));
	parse_cub3d(&data, argv[1]);
	clean_all(&data);
	return (0);
}