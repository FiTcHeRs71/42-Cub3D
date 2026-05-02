/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 20:47:33 by fducrot           #+#    #+#             */
/*   Updated: 2026/05/02 20:47:33 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_array_size(char **array)
{
	int	i;

	i = 0;
	if (!array || !*array)
	{
		return (0);
	}
	while (array[i])
	{
		i++;
	}
	return (i);
}