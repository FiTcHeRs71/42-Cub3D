/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 10:50:54 by fducrot           #+#    #+#             */
/*   Updated: 2026/05/18 10:50:54 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Prints an error message and exits the program cleanly.
 *
 * Frees all allocated resources before quitting,
 * then writes the message to standard error (stderr).
 *
 * @param msg   The error message to display
 * @param data  Pointer to the main structure holding resources to free.
 */
void	ft_error(char *msg, t_data *data)
{
	clean_all(data);
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

/**
 * @brief Prints a contextual error then exits.
 *
 * Output format: "Error\n<what>: <detail>\n".
 * Use when a generic macro is not specific enough and you want to
 * pinpoint the failing subsystem and its cause.
 *
 * @param what    Subsystem / topic (e.g. "Map", "Texture", "Config").
 * @param detail  Specific cause (e.g. "unreadable file: ./tex.xpm").
 * @param data    Pointer to the main structure to free before exit.
 */
void	ft_error_ctx(char *what, char *detail, t_data *data)
{
	clean_all(data);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(what, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(detail, 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}
