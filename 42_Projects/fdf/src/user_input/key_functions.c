/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:06:21 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/09 23:03:28 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//
//-------- these fucntions handles the calclualtion for key user input ---------
//

//	this function calculates the shift of the map with the arrow keys
int	shift_map(t_window *window, int *x_set, int *y_set)
{
	int			speed;

	speed = SHIFT_DEFAULT * (window->height + window->width) / (HEIGHT + WIDTH);
	if (mlx_is_key_down(window->mlx, MLX_KEY_UP)
		&& !mlx_is_key_down(window->mlx, MLX_KEY_DOWN))
		*y_set = range_check(window, 0, -speed, 0);
	if (mlx_is_key_down(window->mlx, MLX_KEY_DOWN)
		&& !mlx_is_key_down(window->mlx, MLX_KEY_UP))
		*y_set = range_check(window, 0, speed, 0);
	if (mlx_is_key_down(window->mlx, MLX_KEY_LEFT)
		&& !mlx_is_key_down(window->mlx, MLX_KEY_RIGHT))
		*x_set = range_check(window, -speed, 0, 0);
	if (mlx_is_key_down(window->mlx, MLX_KEY_RIGHT)
		&& !mlx_is_key_down(window->mlx, MLX_KEY_LEFT))
		*x_set = range_check(window, speed, 0, 0);
	return (1);
}

//	this function nandles the zoom when the user presses P or M
double	zoom_map(t_window *window)
{
	if (window->zoom != ZOOM_DEFAULT)
		return (0);
	if ((mlx_is_key_down(window->mlx, MLX_KEY_P)
			&& !mlx_is_key_down(window->mlx, MLX_KEY_M))
		&& window->zoom == ZOOM_DEFAULT)
		if (window->map_sz.map_area * ZOOM_P < window->max_zoom_size)
			window->zoom = ZOOM_P;
	if (mlx_is_key_down(window->mlx, MLX_KEY_M)
		&& !mlx_is_key_down(window->mlx, MLX_KEY_P)
		&& window->zoom == ZOOM_DEFAULT)
	{
		if (window->map_sz.map_area * ZOOM_M > window->min_zoom_size)
			window->zoom = ZOOM_M;
	}
	return (0);
}

//	this function enables the debug mode and resets the map with the key T
int	debug_mode_map(t_window *window)
{
	static int	key_pressed = 0;

	if (mlx_is_key_down(window->mlx, MLX_KEY_D) && !key_pressed)
	{
		window->debug_mode *= -1;
		if (window->debug_mode == 1)
			mlx_set_window_title(window->mlx, "fdf --DEBUG MODE ENABLED--");
		else
			mlx_set_window_title(window->mlx, "fdf");
		key_pressed = 1;
		return (1);
	}
	else if (!mlx_is_key_down(window->mlx, MLX_KEY_D))
		key_pressed = 0;
	if (mlx_is_key_down(window->mlx, MLX_KEY_T))
	{
		clear_image(window, 0x00000000);
		set_coord(window);
		return (1);
	}
	return (0);
}