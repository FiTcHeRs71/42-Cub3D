/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_whitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:13:05 by fducrot           #+#    #+#             */
/*   Updated: 2026/03/24 17:15:19 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_whitespace(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if ((str[i] < 7 || str[i] > 13) && (str[i] != 32))
			return (0);
		i++;
	}
	return (1);
}
