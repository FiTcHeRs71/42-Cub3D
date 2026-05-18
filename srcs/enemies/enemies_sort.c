/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 10:52:31 by fducrot           #+#    #+#             */
/*   Updated: 2026/05/18 10:52:31 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	compute_distances(t_data *data)
{
	t_enemy	*e;
	double	dx;
	double	dy;

	e = data->enemies;
	while (e)
	{
		dx = data->raycast->pos_x - e->pos_x;
		dy = data->raycast->pos_y - e->pos_y;
		e->dist = dx * dx + dy * dy;
		e = e->next;
	}
}

static void	swap_enemies(t_enemy *a, t_enemy *b)
{
	double	tmp_x;
	double	tmp_y;
	double	tmp_d;

	tmp_x = a->pos_x;
	tmp_y = a->pos_y;
	tmp_d = a->dist;
	a->pos_x = b->pos_x;
	a->pos_y = b->pos_y;
	a->dist = b->dist;
	b->pos_x = tmp_x;
	b->pos_y = tmp_y;
	b->dist = tmp_d;
}

static void	bubble_sort_desc(t_enemy *head)
{
	t_enemy	*cur;
	bool	swapped;

	swapped = true;
	while (swapped)
	{
		swapped = false;
		cur = head;
		while (cur && cur->next)
		{
			if (cur->dist < cur->next->dist)
			{
				swap_enemies(cur, cur->next);
				swapped = true;
			}
			cur = cur->next;
		}
	}
}

void	sort_enemies(t_data *data)
{
	if (!data->enemies)
		return ;
	compute_distances(data);
	bubble_sort_desc(data->enemies);
}
