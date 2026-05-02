/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 20:51:08 by fducrot           #+#    #+#             */
/*   Updated: 2026/05/02 20:51:08 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"
void	*ft_memset(void *s, int c, size_t len)
{
	unsigned char	*tmp;

	tmp = (unsigned char *)s;
	while (len-- > 0)
	{
		*tmp++ = (unsigned char)c;
	}
	return (s);
}
