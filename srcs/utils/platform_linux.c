/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   platform_linux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 00:00:00 by fducrot           #+#    #+#             */
/*   Updated: 2026/07/08 00:00:00 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifndef __APPLE__

int	compat_mouse_move(void *mlx, void *win, int x, int y)
{
	return (mlx_mouse_move(mlx, win, x, y));
}

int	compat_mouse_hide(void *mlx, void *win)
{
	return (mlx_mouse_hide(mlx, win));
}

int	compat_mouse_show(void *mlx, void *win)
{
	return (mlx_mouse_show(mlx, win));
}

int	compat_destroy_display(void *mlx)
{
	return (mlx_destroy_display(mlx));
}

#endif
