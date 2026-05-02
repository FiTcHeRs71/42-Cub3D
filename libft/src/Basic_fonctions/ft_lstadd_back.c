/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 20:48:47 by fducrot           #+#    #+#             */
/*   Updated: 2026/05/02 20:48:51 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_one)
{
	t_list	*last;

	if (!new_one)
	{
		return ;
	}
	if (!*lst)
	{
		*lst = new_one;
		return ;
	}
	last = ft_lstlast(*lst);
	last->next = new_one;
}
