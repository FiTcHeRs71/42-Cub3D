/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 20:47:39 by fducrot           #+#    #+#             */
/*   Updated: 2026/05/02 20:47:45 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_atoi(const char *str)
{
	int	ngps;
	int	result;

	ngps = 1;
	result = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
	{
		str++;
	}
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
		{
			ngps *= -1;
		}
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = ((result * 10) + (*str - 48));
		str++;
	}
	return (result * ngps);
}
