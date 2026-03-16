/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 16/03/2026 18:49:35 by fducrot           #+#    #+#             */
/*   Updated: 16/03/2026 18:49:44 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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