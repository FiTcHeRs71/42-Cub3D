
#include "../../includes/cub3d.h"

/**
 * @brief Prints an error message and exits the program cleanly.
 * 
 * Frees all allocated resources before quitting,
 * then writes the message to standard error (stderr).
 *
 * @param msg   The error message to display
 * @param data  Pointer to the main structure holding resources to free.
 */
void	ft_error(char *msg, t_data *data)
{
	clean_all(data);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}
