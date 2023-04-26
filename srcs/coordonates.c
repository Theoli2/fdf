/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordonates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:16:33 by tlivroze          #+#    #+#             */
/*   Updated: 2023/04/26 21:49:35 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	center_x(int offset, t_data data)
{
	offset = offset;
	data.width = data.width;
	return (WIDTH / 2 - (data.width * offset * data.zoom / 2)
		- (data.height * offset * data.zoom / 2));
}

int	center_y(int offset, t_data data)
{
	offset = offset;
	data.height = data.height;
	return (HEIGHT / 2 - (data.height * offset * data.zoom / 2 / 2)
		- (data.width * offset * data.zoom / 2 / 2));
}

int	calculate_x(int offset, t_vertex tab, t_data data)
{
	int	res ;

	res = ((sin(data.rotate_x * 3.14 / 180) * tab.y * offset - cos \
	(data.rotate_x * 3.14 / 180) * offset * tab.x) / 2 + data.translatex)
		* data.zoom + center_x(offset, data);
	return (res);
}

int	calculate_y(int offset, t_vertex tab, t_data data)
{
	int	res;

	res = ((cos(data.rotate_x * 3.14 / 180) * tab.y * offset + sin \
	(data.rotate_x * 3.14 / 180) * offset * tab.x) / 2 - tab.z * 0.30 * offset
			+ data.translatey) * data.zoom + center_y(offset, data);
	return (res);
}
