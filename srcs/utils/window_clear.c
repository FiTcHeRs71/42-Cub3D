/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 11/05/2026 10:47:57 by fducrot           #+#    #+#             */
/*   Updated: 11/05/2026 10:47:57 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	close_window(t_data *data)
{
	clean_all(data);
	exit(EXIT_SUCCESS);
}
