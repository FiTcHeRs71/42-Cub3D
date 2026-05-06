
#include "includes/cub3d.h"
#include "minilibx-linux/mlx.h"

int	main(int argc, char **argv)
{
	t_data data;

	if (argc != 2)
	{
		ft_putstr_fd(INSTRUCTIONS, 2);
		return (1);
	}
	init_data(&data);
	parse_cub3d(&data, argv[1]);
	init_window(&data, data.mlx);
	load_wall_textures(&data, data.texture, data.mlx);
	mlx_loop(data.mlx->mlx_connect);
	clean_all(&data);
	return (0);
}