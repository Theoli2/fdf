/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 04:14:36 by tlivroze          #+#    #+#             */
/*   Updated: 2023/05/02 01:01:20 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_bonus.h"

int	absolute(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	sign(int n)
{
	return ((n > 0) - (n < 0));
}

void	get_distance(t_drawing *draw)
{
	if (absolute(draw->x1 - draw->x0) > absolute(draw->y1 - draw->y0))
	{
		draw->dist = absolute(draw->x1 - draw->x0);
		draw->is_x = 1;
		draw->pos_start = draw->x0;
	}
	else
	{
		draw->dist = -absolute(draw->y1 - draw->y0);
		draw->is_x = 0;
		draw->pos_start = draw->y0;
	}
}

void	initialize(t_data *data)
{
	data->offset_x = WIDTH / data->width / 2;
	data->offset_y = data->offset_x / 2.;
	data->center_map_x = center_x(*data);
	data->center_map_y = center_y(*data);
}
