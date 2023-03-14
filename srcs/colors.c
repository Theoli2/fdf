/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:11:48 by tlivroze          #+#    #+#             */
/*   Updated: 2023/03/14 20:05:08 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int    get_blue(int index)
{
    index += 100;
    if (index <= 255)
        return (index);
    if (index <= 510)
        return (255);
    if (index <= 765)
        return (765 - index);
    return (0);
}

int    get_red(int index)
{
    index += 100;
    if (765 < index && index <= 1020)
        return (index - 765);
    if (1020 < index && index <= 1275)
        return (255);
    if (1275 < index && index <= 1430)
        return (1530 - index);
    return (0);
}

int    get_green(int index)
{
    index += 100;
    if (255 < index && index <= 510)
        return (index - 255);
    if (510 < index && index <= 1020)
        return (255);
    if (1020 < index && index <= 1275)
        return (1275 - index);
    return (0);
}

int    get_perfect_gradient(t_data *data, int alt)
{
    int    color;
    int    index;
    int    delta_alt;

    delta_alt = data->draw.tallest - data->draw.lowest;
    index = 1330 * (alt - data->draw.lowest) / delta_alt;
    color = get_blue(index);
    color += get_green(index) << 8;
    color += get_red(index) << 16;
    return (color);
}

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
