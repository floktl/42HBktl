/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo <flo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:14:49 by fkeitel           #+#    #+#             */
/*   Updated: 2024/03/18 21:05:58 by flo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../fdf.h"

//
//-------------- functions to prevent leaks and for cleaning up ----------------
//

//	function for freeing all values within a stack
void	free_stack(t_coord **stack)
{
	t_coord	*head;
	t_coord	*tmp;

	if (!stack)
		return ;
	head = *stack;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
	free(stack);
}

//	function to free an two dimensional array of chars
void	free_two_dimensional_array(char **param)
{
	int	count;

	count = 0;
	if (!param)
		return ;
	while (param[count])
	{
		free(param[count]);
		count++;
	}
	free(param);
}

//	function to reset all pixelsof the window to its default colors
void	clear_image(t_window *window, uint32_t color)
{
	int	x;
	int	y;

	y = 0;
	while (y < window->mlx->height)
	{
		x = 0;
		while (x < window->mlx->width)
		{
			mlx_put_pixel(window->image, x, y, color);
			x++;
		}
		y++;
	}
}

//	function to free an 3 dimensional array of integers
void	free_map(int ***map)
{
	int	i;
	int	j;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			free(map[i][j]);
			map[i][j] = NULL;
			j++;
		}
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	*map = NULL;
}
