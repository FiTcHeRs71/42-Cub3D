/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 13:50:51 by fducrot           #+#    #+#             */
/*   Updated: 2026/05/18 13:50:51 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	real_len;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	real_len = ft_strlen(s) - start;
	if (real_len > len)
		real_len = len;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	str = ft_calloc(real_len + 1, sizeof(char));
	if (!str)
	{
		return (NULL);
	}
	while (i < real_len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
