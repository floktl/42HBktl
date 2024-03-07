/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assigning_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 07:33:01 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/07 16:38:52 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

int	map_size_default_setting(t_sz *map_sz, t_sz size)
{
	map_sz->xposmw = WIDTH / 2;
	map_sz->yposmw = HEIGHT / 2;
	map_sz->zcentmw = 0;
	map_sz->xm_rot_deg = 0;
	map_sz->ym_rot_deg = 0;
	map_sz->zm_rot_deg = 0;
	map_sz->maxsz_x_p = 0;
	map_sz->maxsz_x_m = 0;
	map_sz->maxsz_x_p = 0;
	map_sz->maxsz_x_m = 0;
	map_sz->xm_size = size.xm_size;
	map_sz->ym_size = size.ym_size;
	return (0);
}

void	update_mapsize(t_sz *map_sz, t_coord *temp)
{
	if (map_sz->maxsz_x_p < temp->xm)
		map_sz->maxsz_x_p = round(temp->xm);
	if (map_sz->maxsz_x_m > temp->xm)
		map_sz->maxsz_x_m = round(temp->xm);
	if (map_sz->maxsz_y_p < temp->ym)
		map_sz->maxsz_y_p = round(temp->ym);
	if (map_sz->maxsz_y_m > temp->ym)
		map_sz->maxsz_y_m = round(temp->ym);
}

void	set_default_window_data(t_window *window)
{
	window->start_size = (WIDTH / (window->map_sz.xm_size + 2));
	window->zoom_factor = window->start_size;
	window->last_zoom_faktor = window->zoom_factor;
	window->cent_xw = WIDTH / 2;
	window->cent_yw = HEIGHT / 2;
	window->mouse_posx = window->cent_xw;
	window->mouse_posy = window->cent_yw;
	window->map_sz.xm_offset = 0.0;
	window->map_sz.ym_offset = 0.0;
	window->map_sz.zm_offset = 0.0;
	window->map_sz.xposmw = WIDTH / 2;
	window->map_sz.yposmw = HEIGHT / 2;
	window->debug_mode = -1;
	window->width = WIDTH;
	window->height = HEIGHT;
}

//polarAngle corresponds to the inclination or zenith angle.
//azimuthalAngle corresponds to the angle measured in the x-y plane.
//additionalAngle corresponds to the third angle representing rotation or tilt.

int	assign_degree_len_color(t_window *window, t_coord *new)
{
	new->deg_xm = calc_angle(new->xm, new->ym, 'X');
	new->deg_ym = calc_angle(-new->ym, new->xm, 'Y');
	new->deg_zm = calc_angle(new->ym, new->zm, 'Z');
	new->len_cent = ft_sqrt((new->xm * new->xm)
			+ (new->ym * new->ym) + (new->zm * new->zm));
	new->color = ft_pixel(0xFF, 0xFF
			- (new->zm * (255 / (window->map_sz.zmcent_plus + 1))), 0xFF
			- (new->zm * (255 / (window->map_sz.zmcent_minus - 1))), 0xFF);
	return (0);
}

int	assign_coord_position(t_window *window, t_coord *new, int x, int y)
{
	double	round_x;
	double	round_y;

	round_x = 0.0;
	if (window->map_sz.xm_size % 2 == 1)
		round_x = 0.5;
	round_y = 0.0;
	if (window->map_sz.ym_size % 2 == 1)
		round_y = 0.5;
	new->xm = -((window->map_sz.xm_size * window->zoom_factor) / 2)
		+ ((x + round_x) * window->zoom_factor);
	new->ym = ((window->map_sz.ym_size * window->zoom_factor) / 2)
		- ((y + round_y) * window->zoom_factor);
	new->zm = ft_atoi(window->map[y][x])
		+ window->map_sz.zm_offset;
	new->xw = round(new->xm) + window->cent_xw;
	new->yw = -round(new->ym) + window->cent_yw;
	new->zw = round(new->zm) + 0;
	return (0);
}