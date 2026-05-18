/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 10:53:17 by fducrot           #+#    #+#             */
/*   Updated: 2026/05/18 10:53:17 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include "minilibx-linux/mlx.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putstr_fd(ERR_USAGE, 2);
		return (1);
	}
	init_data(&data);
	parse_cub3d(&data, argv[1]);
	init_window(&data, data.mlx);
	init_mini_map(&data);
	mlx_loop(data.mlx->mlx_connect);
	clean_all(&data);
	return (0);
}
