/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:11:48 by tlivroze          #+#    #+#             */
/*   Updated: 2023/05/05 01:20:35 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_bonus.h"

//cherche la hauteur la plus basse et la plus haute 
//dans tout le tableau
void	lowest_tallest(t_data *data)
{
	int	x;
	int	y;

	data->draw.lowest = data->tab[0][0].z;
	data->draw.tallest = data->tab[0][0].z;
	x = 0;
	while (x < data->width)
	{
		y = 0;
		while (y < data->height)
		{
			if (data->tab[x][y].z < data->draw.lowest)
				data->draw.lowest = data->tab[x][y].z;
			if (data->tab[x][y].z > data->draw.tallest)
				data->draw.tallest = data->tab[x][y].z;
			y++;
		}
		x++;
	}
}
