/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordonates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:16:33 by tlivroze          #+#    #+#             */
/*   Updated: 2023/05/03 01:22:29 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

float	center_x(t_data data)
{
	float	res;

	res = ((sin(45 * 3.14 / 180) * ((data.height - 1) / 2.) * data.offset_x - \
	cos(45 * 3.14 / 180) * data.offset_x * ((data.width - 1) / 2.)) / 2);
	return (res);
}

float	center_y(t_data data)
{
	float	res;

	res = ((cos(45 * 3.14 / 180) * ((data.height - 1) / 2.) * data.offset_y \
	+ sin(45 * 3.14 / 180) * data.offset_y * ((data.width - 1) / 2.)) / 2);
	return (res);
}

int	calculate_x(float offset, t_vertex tab, t_data data)
{
	int	res;

	res = ((sin(45 * 3.14 / 180) * tab.y * offset - \
	cos(45 * 3.14 / 180) * offset * tab.x) / 2) \
	+ WIDTH / 2 - data.center_map_x;
	return (res);
}

int	calculate_y(float offset, t_vertex tab, t_data data)
{
	int	res;

	res = ((cos(45 * 3.14 / 180) * tab.y * offset + sin(45 * 3.14 / 180) * \
	offset * tab.x) / 2 - tab.z * 0.30 * \
	offset) + HEIGHT / 2 - data.center_map_y;
	return (res);
}
