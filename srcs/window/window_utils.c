/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 10:51:13 by fducrot           #+#    #+#             */
/*   Updated: 2026/05/18 10:51:13 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	release_mouse(t_data *data)
{
	compat_mouse_show(data->mlx->mlx_connect, data->mlx->mlx_window);
	data->mouse_active = false;
}

int	handle_key_press(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys.w = true;
	else if (keycode == KEY_A)
		data->keys.a = true;
	else if (keycode == KEY_S)
		data->keys.s = true;
	else if (keycode == KEY_D)
		data->keys.d = true;
	else if (keycode == KEY_E)
		toggle_nearest_door(data);
	else if (keycode == KEY_LEFT)
		data->keys.left = true;
	else if (keycode == KEY_RIGHT)
		data->keys.right = true;
	else
		handler_bonus_key(keycode, data);
	return (0);
}

int	handle_key_release(int keycode, t_data *data)
{
	if (keycode == KEY_W)
		data->keys.w = false;
	else if (keycode == KEY_A)
		data->keys.a = false;
	else if (keycode == KEY_S)
		data->keys.s = false;
	else if (keycode == KEY_D)
		data->keys.d = false;
	else if (keycode == KEY_LEFT)
		data->keys.left = false;
	else if (keycode == KEY_RIGHT)
		data->keys.right = false;
	return (0);
}

int	focus_in(t_data *data)
{
	reset_mouse_to_center(data);
	return (0);
}

int	focus_out(t_data *data)
{
	data->mouse_active = false;
	return (0);
}
