/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 10:51:05 by fducrot           #+#    #+#             */
/*   Updated: 2026/05/18 10:51:05 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handler_bonus_key(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_window(data);
	else if (keycode == XK_Tab)
	{
		if (data->mouse_active)
			release_mouse(data);
		else
			reset_mouse_to_center(data);
	}
	else if (keycode == XK_m)
		toggle_minimap_fullscreen(data);
	else if (keycode == XK_e)
		toggle_nearest_door(data);
	return (0);
}
