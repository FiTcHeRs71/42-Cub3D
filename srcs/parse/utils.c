
#include "../../includes/cub3d.h"
#include <stdbool.h>

bool	checker_before_split(char *line, char sep)
{
	int	i;
	int	count_sep;

	i = 0;
	count_sep = 0;
	while (line[i])
	{
		if (line[i] == sep)
			count_sep ++;
		else
			count_sep = 0;
		if (count_sep > 1)
			return (false);
		i++;
	}
	return (true);
}
