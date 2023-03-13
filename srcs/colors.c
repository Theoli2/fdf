/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:11:48 by tlivroze          #+#    #+#             */
/*   Updated: 2023/03/09 20:08:29 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	lowest(int z, t_data data)
{
	if (z < data.draw.lowest)
		return (z);
	else
		return (data.draw.lowest);
}

int	tallest(int z, t_data data)
{
	if (z > data.draw.tallest)
		return (z);
	else
		return (data.draw.tallest);
}

int	color_point(int height, t_data *data)
{
	int	dist;
	int	color_index;
	int	color;

	color = 0;
	dist = data->draw.tallest - data->draw.lowest;
	color_index = 664 * height / dist;
	if (color_index <= 155)
		color = color_index + 100;
	else if (color_index <= 410) 
	{
		color = 255 - (color_index - 155);
		color = (color_index - 155) << 8;
	}
	else if (color_index <= 664)
	{
		color = (410 - (color_index - 255)) << 8;
		color = (color_index - 410) << 16;
	}
	return (color);
}
