/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_gradient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:29:31 by tlivroze          #+#    #+#             */
/*   Updated: 2023/05/02 01:01:47 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_bonus.h"

int	get_blue(int index)
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

int	get_red(int index)
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

int	get_green(int index)
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

int	get_perfect_gradient(t_data *data, int alt)
{
	int	color;
	int	index;
	int	delta_alt;

	delta_alt = data->draw.tallest - data->draw.lowest;
	if (delta_alt == 0)
		return (155);
	index = 1330 * (alt - data->draw.lowest) / delta_alt;
	color = get_blue(index);
	color += get_green(index) << 8;
	color += get_red(index) << 16;
	return (color);
}
