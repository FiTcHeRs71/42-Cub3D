
#include "../../includes/cub3d.h"

void	ft_error(char *msg, t_data *data)
{
	(void)data;
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}