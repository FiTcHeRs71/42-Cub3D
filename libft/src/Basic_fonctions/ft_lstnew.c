/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 20:50:30 by fducrot           #+#    #+#             */
/*   Updated: 2026/05/02 20:50:30 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_elem;

	new_elem = ft_calloc(1, sizeof(t_list));
	if (!new_elem)
	{
		return (NULL);
	}
	new_elem->content = content;
	new_elem->next = NULL;
	return (new_elem);
}
