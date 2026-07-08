/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 00:00:00 by fducrot           #+#    #+#             */
/*   Updated: 2026/07/08 00:00:00 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

/*
** Cross-platform layer for minilibx (Linux X11 <-> macOS Metal / mms).
** Provides uniform key macros and wrappers for the mlx calls whose
** signatures differ between the two implementations.
*/

#ifndef KEYS_H
# define KEYS_H

# ifdef __APPLE__

#  include "../minilibx-macos/mlx.h"

/* macOS hardware keycodes (kVK_ANSI_*) delivered by minilibx mms */
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_E 14
#  define KEY_M 46
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_ESC 53
#  define KEY_TAB 48

# else

#  include "../minilibx-linux/mlx.h"
#  include <X11/keysym.h>

/* Linux: X11 keysyms */
#  define KEY_W XK_w
#  define KEY_A XK_a
#  define KEY_S XK_s
#  define KEY_D XK_d
#  define KEY_E XK_e
#  define KEY_M XK_m
#  define KEY_LEFT XK_Left
#  define KEY_RIGHT XK_Right
#  define KEY_ESC XK_Escape
#  define KEY_TAB XK_Tab

# endif

/*
** Platform wrappers (defined in srcs/utils/platform.c) for the mlx calls
** whose signatures differ between Linux (X11) and macOS (mms):
**   - mlx_mouse_move: 4 args on Linux, 3 on macOS
**   - mlx_mouse_hide / mlx_mouse_show: 2 args on Linux, 0 on macOS
**   - mlx_destroy_display: only exists on Linux
*/
int	compat_mouse_move(void *mlx, void *win, int x, int y);
int	compat_mouse_hide(void *mlx, void *win);
int	compat_mouse_show(void *mlx, void *win);
int	compat_destroy_display(void *mlx);

#endif
