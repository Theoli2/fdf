/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordonates.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:16:33 by tlivroze          #+#    #+#             */
/*   Updated: 2023/05/05 02:05:37 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_bonus.h"

//renvoie le nombre de pixel en x necessaires pour centrer la map
//en prenant en compte la rotation et le zoom
float	center_x(t_data data)
{
	float	res;

	res = ((sin(data.rotate_x * 3.14 / 180) * ((data.height - 1) / 2.) * \
	data.offset_x - cos(data.rotate_x * 3.14 / 180) * data.offset_x * \
	((data.width - 1) / 2.)) / 2) * data.zoom;
	return (res);
}

//renvoie le nombre de pixel en y necessaires pour centrer la map
float	center_y(t_data data)
{
	float	res;

	res = ((cos(data.rotate_x * 3.14 / 180) * ((data.height - 1) / 2.) * \
	data.offset_y + sin(data.rotate_x * 3.14 / 180) * data.offset_y * \
	((data.width - 1) / 2.)) / 2) * data.zoom;
	return (res);
}

//calcule la coordonnee en x d'un point en prenant en compte
//les variables de rotation, de translation et de zoom
int	calculate_x(float offset, t_vertex tab, t_data data)
{
	int	res ;

	res = ((sin(data.rotate_x * 3.14 / 180) * tab.y * offset - cos \
	(data.rotate_x * 3.14 / 180) * offset * tab.x) / 2 + data.translatex) \
	* data.zoom + WIDTH / 2 - data.center_map_x;
	return (res);
}

//calcule la coordonnee en y d'un point en prenant en compte
//les variables de rotation, de translation et de zoom
int	calculate_y(float offset, t_vertex tab, t_data data)
{
	int	res;

	res = ((cos(data.rotate_x * 3.14 / 180) * tab.y * offset + sin \
	(data.rotate_x * 3.14 / 180) * offset * tab.x) / 2 - tab.z * 0.30 * \
	offset + data.translatey) * data.zoom + HEIGHT / 2 - data.center_map_y;
	return (res);
}
