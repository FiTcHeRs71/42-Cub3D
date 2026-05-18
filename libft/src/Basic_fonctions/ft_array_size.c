/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:51:10 by fducrot           #+#    #+#             */
/*   Updated: 2026/05/18 13:51:10 by fducrot          ###   ########.ch       */
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
