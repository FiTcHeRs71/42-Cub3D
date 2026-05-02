/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 20:52:39 by fducrot           #+#    #+#             */
/*   Updated: 2026/05/02 20:52:39 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*tmp1;
	unsigned char	*tmp2;

	tmp1 = (unsigned char *)s1;
	tmp2 = (unsigned char *)s2;
	while ((*tmp1 || *tmp2) && (n > 0))
	{
		if (*tmp1 != *tmp2)
		{
			return (*tmp1 - *tmp2);
		}
		tmp1++;
		tmp2++;
		n--;
	}
	return (0);
}
