/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_gradient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 19:57:54 by tlivroze          #+#    #+#             */
/*   Updated: 2023/05/02 01:01:30 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf_bonus.h"

int	line_gradient(t_drawing draw, t_vertex start, t_vertex end)
{
	int		cur_dist;
	t_color	col;

	if (draw.is_x)
		cur_dist = absolute(draw.x0 - draw.pos_start);
	else
		cur_dist = -absolute(draw.y0 - draw.pos_start);
	col.d_r = ((end.color & (255 << 16)) - (start.color & (255 << 16))) >> 16;
	col.d_g = ((end.color & (255 << 8)) - (start.color & (255 << 8))) >> 8;
	col.d_b = (end.color & 255) - (start.color & 255);
	if (draw.dist != 0)
	{
		col.r = ((start.color & (255 << 16)) >> 16) \
		+ (col.d_r * cur_dist / draw.dist);
		col.g = ((start.color & (255 << 8)) >> 8) \
		+ (col.d_g * cur_dist / draw.dist);
		col.b = (start.color & 255) + (col.d_b * cur_dist / draw.dist);
	}
	else
		return (start.color);
	return (col.b + (col.g << 8) + (col.r << 16));
}
