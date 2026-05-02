/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 20:48:40 by fducrot           #+#    #+#             */
/*   Updated: 2026/05/02 20:48:40 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

size_t	ft_count_int(int nbr)
{
	int	count;

	count = 0;
	if (nbr == 0)
	{
		count = 1;
		return (count);
	}
	if (nbr < 0)
	{
		nbr *= -1;
		count++;
	}
	while (nbr != 0)
	{
		nbr /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t		i;
	size_t		len;
	long int	nbr;
	char		*result;

	i = 0;
	len = ft_count_int(n);
	nbr = n;
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (nbr < 0)
	{
		result[0] = '-';
		nbr *= -1;
		i++;
	}
	while (len > i)
	{
		len--;
		result[len] = (nbr % 10) + 48;
		nbr /= 10;
	}
	return (result);
}
