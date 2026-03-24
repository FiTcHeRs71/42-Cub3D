
#include "../../includes/cub3d.h"

void	ft_error(char *msg, t_data *data)
{
	clean_all(data);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}
