/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_anim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 10:47:51 by fducrot           #+#    #+#             */
/*   Updated: 2026/05/18 10:47:51 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	update_enemy_animation(t_data *data)
{
	data->enemy_anim.frame_counter++;
	if (data->enemy_anim.frame_counter < ENEMY_ANIM_SPEED)
		return ;
	data->enemy_anim.frame_counter = 0;
	data->enemy_anim.current_frame++;
	if (data->enemy_anim.current_frame >= ENEMY_FRAMES)
		data->enemy_anim.current_frame = 0;
}
