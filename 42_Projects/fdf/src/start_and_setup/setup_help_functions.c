/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_help_functions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkeitel <fkeitel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:36:30 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/07 07:18:32 by fkeitel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//	find and sets a pointer to the last coordinate in y direction (before_y)
void	ft_set_before_y(t_coord **head, int iterations, t_window *window)
{
	t_coord	*current;
	int		count_temp;
	t_coord	*temp;

	current = *head;
	count_temp = iterations - window->map_sz.xm_size;
	temp = NULL;
	while (current != NULL && iterations >= 0)
	{
		if (count_temp == 0)
		{
			temp = current;
			count_temp = -1;
		}
		else if (count_temp > 0)
			count_temp--;
		if (iterations == 0)
		{
			if (temp != NULL)
				current->before_y = temp;
			break ;
		}
		current = current->next;
		iterations--;
	}
}

//	find and sets a pointer to the next coordinate in y direction (next_y)
void	ft_set_after_y(t_coord *head, t_window *window)
{
	t_coord	*current;
	t_coord	*current2;
	int		counter;

	current = head;
	while (current != NULL)
	{
		counter = 0;
		current2 = current;
		while (current2 != NULL && counter <= window->map_sz.xm_size)
		{
			if (counter == window->map_sz.xm_size)
				current->next_y = current2;
			current2 = current2->next;
			counter++;
		}
		current = current->next;
	}
}

//	returns the necessary iterations of coordinate to the next y value (same x)
int	get_index(t_window *window, int pos_xm, int pos_ym)
{
	if (pos_xm < 1 || pos_ym < 1
		|| pos_xm > window->map_sz.xm_size || pos_ym > window->map_sz.ym_size)
	{
		return (-1);
	}
	return (window->map_sz.xm_size * (pos_ym) + (pos_xm - 1));
}

//	this function returns a new coordinate to the map and links the 4 neighbour
//	coordinates (in x and y direction)
t_coord	*link_add_pt(t_coord **coord, t_window *window, int x, int y)
{
	static t_coord	*last = NULL;
	t_coord			*new_coord;

	new_coord = malloc(sizeof(t_coord));
	if (!new_coord)
		return (NULL);
	new_coord->next = NULL;
	new_coord->next_y = NULL;
	new_coord->pos_xm = x + 1;
	new_coord->pos_ym = y + 1;
	if (new_coord->pos_xm == 1)
		new_coord->before = NULL;
	else
		new_coord->before = last;
	ft_add_back(coord, new_coord);
	if (new_coord->pos_ym < 1)
		new_coord->before_y = NULL;
	else
		ft_set_before_y(coord, get_index(window, new_coord->pos_xm,
				new_coord->pos_ym - 1), window);
	last = new_coord;
	return (new_coord);
}