
#include "../../includes/cub3d.h"

int	close_window(t_mlx *mlx, t_data *data)
{
	if (mlx && mlx->mlx_connect)
	{
		mlx_destroy_display(mlx->mlx_connect);
		free(mlx->mlx_connect);
	}
	clean_all(data);
	exit(EXIT_SUCCESS);
}